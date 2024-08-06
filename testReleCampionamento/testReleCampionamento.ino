#include <Wire.h>
#include "Adafruit_INA219.h"

Adafruit_INA219 ina219;

#define NUM_RELE 16

const int relePins[NUM_RELE] = {
  22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37
};

struct Data {
  float voltage;
  float current;
} samples[NUM_RELE];

void attivaRele(int index) {
  digitalWrite(relePins[index], HIGH);
}

void disattivaRele(int index) {
  digitalWrite(relePins[index], LOW);
}

void stampaResocontoFinale() {
  Serial.println("Resoconto Finale:");
  for (int i = 0; i < NUM_RELE; i++) {
    // Stampa i dati per il Serial Plotter
    Serial.print("Rele ");
    Serial.print(i + 1);
    Serial.print(": Tensione = ");
    Serial.print(samples[i].voltage);
    Serial.print(" V, Corrente = ");
    Serial.print(samples[i].current);
    Serial.println(" mA");
  }
}

void misuraCorrenteTensione() {
  float shuntVoltage = ina219.getShuntVoltage_mV();
  float busVoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();
  float loadVoltage = busVoltage + (shuntVoltage / 1000);
  
  Serial.print("Misura: Tensione = ");
  Serial.print(loadVoltage);
  Serial.print(" V, Corrente = ");
  Serial.print(current_mA);
  Serial.println(" mA");
}


void setup() {
  Serial.begin(115200);
  while (!Serial) ; // Attesa connessione seriale

  for (int i = 0; i < NUM_RELE; i++) {
    pinMode(relePins[i], OUTPUT);
    digitalWrite(relePins[i], LOW); // Assicurati che i relè siano spenti all'avvio
  }

 ina219.begin();
}

void loop() {
   String command;
  if (Serial.available() > 0) {
    command = Serial.readStringUntil('\n');
    command.trim(); // Rimuove spazi bianchi e nuove linee

    if (command == "test") {
     for (int i = 0; i < NUM_RELE; i++) {
        attivaRele(i);
        delay(200); // Dà tempo al sistema di stabilizzarsi
        
        float shuntVoltage = ina219.getShuntVoltage_mV();
        float busVoltage = ina219.getBusVoltage_V();
        float current_mA = ina219.getCurrent_mA();
        //float power_mW = ina219.getPower_mW();
        float loadVoltage = busVoltage + (shuntVoltage / 1000);
        //float adcVoltage = analogRead(0) * 5.0 / 1023.0;
        //float current_mA = shuntVoltage * 0.1;
        samples[i].voltage = loadVoltage; // Usa la tensione effettiva del carico
        samples[i].current = current_mA; // Usa la corrente misurata
        
        Serial.print("Rele ");
        Serial.print(i + 1);
        Serial.print(": Tensione = ");
        Serial.print(samples[i].voltage);
        Serial.print(" V, Corrente = ");
        Serial.println(samples[i].current);
        Serial.println(" mA");

       
        disattivaRele(i);
      }
      stampaResocontoFinale();
    } else if (command.startsWith("rele")) {
      // Estrae il numero del relè dal comando
      int releNum = command.substring(4).toInt();
      if (releNum >= 1 && releNum <= NUM_RELE) {
        Serial.print("Attivazione Rele ");
        Serial.println(releNum);
        
        attivaRele(releNum - 1); // -1 perché l'array parte da 0
        delay(10000); // Attiva il relè per 10 secondi
        
        float shuntVoltage = ina219.getShuntVoltage_mV();
        float busVoltage = ina219.getBusVoltage_V();
        float current_mA = ina219.getCurrent_mA();
        float power_mW = ina219.getPower_mW();
        float loadVoltage = busVoltage + (shuntVoltage / 1000);
        
        Serial.print("Rele ");
        Serial.print(releNum);
        Serial.print(": Tensione = ");
        Serial.print(loadVoltage);
        Serial.print(" V, Corrente = ");
        Serial.print(current_mA);
        Serial.print(" mA");
        
        disattivaRele(releNum - 1);
        
        Serial.print("Rele ");
        Serial.print(releNum);
        Serial.println(" disattivato.");
      } else {
        Serial.println("Numero di relè non valido.");
      }
    }
    else if (command == "misura") {
      misuraCorrenteTensione();
    }
  }
}
