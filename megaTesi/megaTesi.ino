#include <MemoryFree.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Adafruit_INA219.h"
// Funzione per testare tutti i relè
void testRelays();
// Funzione per gestire i comandi inviati tramite seriale
void handleRelayCommand(String command);
// Funzione per avviare il campionamento dei dati
void campionaDati();
// Funzione per verificare la variazione della luminosità
bool verificaVariazioneLuminosita();
// Funzione per attivare un relè
void attivaRele(int relayPin);
// Funzione per disattivare un relè
void disattivaRele(int relayPin);
// Funzione per visualizzare i dati
void visualizzaDati();
// Funzione per calcolare il Massimo Power Point (MPP)
void calcolaMPP();

float shuntVoltage;
float busVoltage;
float current_mA;
float power_mW;
float loadVoltage;
float adcVoltage;



#define PIN_RELE_1 22
#define PIN_RELE_2 23
#define PIN_RELE_3 24
#define PIN_RELE_4 25
#define PIN_RELE_5 26
#define PIN_RELE_6 27
#define PIN_RELE_7 28
#define PIN_RELE_8 29
#define PIN_RELE_9 30
#define PIN_RELE_10 31
#define PIN_RELE_11 32
#define PIN_RELE_12 33
#define PIN_RELE_13 34
#define PIN_RELE_14 35
#define PIN_RELE_15 36
#define PIN_RELE_16 37

String inString; // stringa del comando da comando seriale
 Adafruit_INA219 ina219;

//VARIABILI PER CAMPIONAMENTO DATI
#define PIN_RELE_START 22  //Numero del primo pin gitale usato per i 16 rele
#define NUM_RELE 16 // QUANTITA DEI RELE UTILIZZATI
#define SAMPLING_TIME 100  // (CAMPIONAMENTO) 3 secondi di campionamento per ogni rele
#define DELAY_BETWEEN_RELE 100  // (CAMPIONAMENTO) Attendi 1 secondo tra ogni rele e l'altro 
#define MAX_NUM_SAMPLES 16 //numero di coppie di valori da campionare delle 16 resistenze

//Struttura dati per conservare coppia corrente e voltaggio di oguna delle 16 resistenze di carico
struct Sample {
  float voltage=0;
  float current=0;
};
Sample samples[NUM_RELE];

Sample campiona() {
    Sample sample;

    shuntVoltage = ina219.getShuntVoltage_mV();
     busVoltage = ina219.getBusVoltage_V();
    current_mA = ina219.getCurrent_mA();
    power_mW = ina219.getPower_mW();
    loadVoltage = busVoltage + (shuntVoltage / 1000);

    sample.voltage =loadVoltage;
    sample.current = current_mA;

    return sample;
}



void setup() {
  // Inizializzazione dei pin dei rele
  for (int i = 1; i <= NUM_RELE; ++i) {
    pinMode(PIN_RELE_START + i - 1, OUTPUT);
    digitalWrite(PIN_RELE_START + i - 1, LOW);
  }
  // Inizializza l'oggetto INA219
  ina219.begin();
  // Inizializzazione della comunicazione seriale
  Serial.begin(115200); // SERIALE DI MEGA
  Serial3.begin(115200); // SERIALE DI ESP
}


void loop() {



  // CODICE PER AVVIARE IL CAMPIONAMENTO DA SERIALE
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command == "campiona") {
        campionaDati();
        calcolaMPP();
    } 
}

}// FILE LOOP

  // ascolto i messaggi che provengono da esp
  void serialEvent3() {
    while (Serial3.available()) {
      char inChar = Serial3.read();
      Serial.write(inChar); //SCRIVE LA VARIABILE DEL CODICE SULLA SERIALE DI MEGA
      inString += inChar;
      if (inChar == '\n'){  // Verifica se il carattere letto è una nuova linea'\n'
        handleRelayCommand(inString);// Gestisce il comando quando viene rilevata la fine della stringa
        inString = "" ;  // Resetta la stringa per il prossimo comando
      }
    }
  }

  // QUESTA FUNZIONE ATTIVA CON ON0 IL CAMPIONAMENTO AUTOMATICO DI TUTTI I DATI
  //OPPURE PUOI ATTIVARE I COMANDI SEPARATAMENTE E QUANTO LI HA TUTTI MANDA IL CAMPIONAMENTO
  int samplesCount = 0;// Dichiarazione di un array per tenere traccia del numero di campioni raccolti per ogni comando
  int currentCommand = -1;// Variabile per tenere traccia del comando corrente
 void handleRelayCommand(String command) {
  int relayNumber;
  if (command.startsWith("ON")) {
    relayNumber = command.substring(2).toInt();
    if (relayNumber >= 0 && relayNumber <= 16) {
      if (relayNumber == 0) {
        // Se il comando è "ON0", avvia il campionamento automatico di tutti i dati
        campionaDati();
        currentCommand = -1;  // Azzera il comando corrente
        samplesCount = 0;
        calcolaMPP();
      } else {
        // Altrimenti, gestisci i comandi da "ON1" a "ON16"
        currentCommand = relayNumber - 1;
        attivaRele(PIN_RELE_START + currentCommand);
        delay(SAMPLING_TIME);
        samples[currentCommand] = campiona();
        disattivaRele(PIN_RELE_START + currentCommand);
      }
    }
  }
  if (currentCommand != -1) {
    // Se il comando corrente è impostato, campiona e memorizza i dati
    samples[currentCommand] = campiona();
    samplesCount++;
    if (samplesCount >= MAX_NUM_SAMPLES) {
      calcolaMPP();
      currentCommand = -1; // Azzera il comando corrente
      samplesCount = 0;
    }
  }
}


  // FUNZIONI PER IL CAMPIONAMENTO
  void campionaDati() {
    for (int i = 0; i < NUM_RELE; ++i) {
      int relayPin = PIN_RELE_START + i;
      attivaRele(relayPin);
      delay(SAMPLING_TIME);
      samples[i] = campiona();
      disattivaRele(relayPin);
      delay(DELAY_BETWEEN_RELE);
    }
  }
  void attivaRele(int relayPin) {
    digitalWrite(relayPin, HIGH);
  }
  void disattivaRele(int relayPin) {
    digitalWrite(relayPin, LOW);
  }
  // Funzione per implementare l'algoritmo P&O
  float mpp_po(float *tensione, float *corrente, int n, float step) {
      float massimo = 0;
      int indice_massimo = 0;
      float tensione_pre = tensione[0];
      float potenza_pre = potenza(tensione_pre, corrente[0]);

      // Iterazione sulle coppie di valori
      for (int i = 1; i < n; i++) {
        float potenza_attuale = potenza(tensione[i], corrente[i]);

        // Calcolo della variazione di potenza
        float delta_potenza = potenza_attuale - potenza_pre;

        // Perturbazione della tensione
        if (delta_potenza > 0) tensione[i] += step;
          else tensione[i] -= step;
        
        // Aggiornamento del massimo
        if (potenza_attuale > massimo) {
          massimo = potenza_attuale;
          indice_massimo = i;
        }

        // Memorizzazione dei valori precedenti
        tensione_pre = tensione[i];
        potenza_pre = potenza_attuale;
      }
      // Restituisce la tensione al punto di massima potenza
      return tensione[indice_massimo];
  }
  // Funzione per calcolare la potenza
  float potenza(float tensione, float corrente){
      return tensione * corrente;
  }

  void calcolaMPP() {
    float tensioneMPP = 0.0;
    float correnteMPP = 0.0;
    float potenzaMPP = 0.0;

    // Inizializzazione delle variabili per l'algoritmo Perturb and Observe (P&O)
    const int NUM_SAMPLES = NUM_RELE; // Numero di campioni
    float tensione[NUM_SAMPLES]; // Array per le tensioni dei campioni
    float corrente[NUM_SAMPLES]; // Array per le correnti dei campioni
    float step = 0.1; // Passo di perturbazione

    // Riempimento degli array con i valori dei campioni
    for (int i = 0; i < NUM_SAMPLES; ++i) {
      tensione[i] = samples[i].voltage;
      corrente[i] = samples[i].current;
    }
    // Calcolo del MPP utilizzando l'algoritmo P&O
    tensioneMPP = mpp_po(tensione, corrente, NUM_SAMPLES, step);
    // Calcolo della corrente MPP corrispondente
    for (int i = 0; i < NUM_SAMPLES; ++i) {
      if (tensione[i] == tensioneMPP) {
        correnteMPP = corrente[i];
        break;
      }
    }
    // Calcolo della potenza MPP corrispondente
    potenzaMPP = tensioneMPP * correnteMPP;
    
    // Invia i risultati tramite Serial3 mega->esp
    Serial3.print(tensioneMPP, 2);
    Serial3.print(" ");
    Serial3.print(correnteMPP, 2);
    Serial3.print(" ");
    Serial3.println(potenzaMPP, 2);
    
    // Invia i dati campionati (16 coppie di valori) tramite Serial3
    for (int i = 0; i < NUM_RELE; ++i) {
        Serial3.print(samples[i].voltage, 2);
        Serial3.print(" ");
        Serial3.print(samples[i].current, 2);
        Serial3.print(" ");
    }
    Serial3.println();  // Aggiungi una nuova linea alla fine  
}




