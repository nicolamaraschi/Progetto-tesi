#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>        // Include the ArduinoJson header
 


const char* ssid = "iPhone di admin";
const char* password = "123456789";
const char* hostName = "esp8266";
// VARIABILE PER MANDARE DATI DA ESP AL SERVER
String commandToServer = "";
String inString = "";
float dataPairs[16][2];  // Array per memorizzare le coppie di dati campionati
#define NUM_RELE 16

float voltageMPP = 0.0;
float currentMPP = 0.0;
float powerMPP = 0.0;

struct Sample {
  float voltage=0;
  float current=0;
};
// Dichiarazione di un array di strutture Sample per memorizzare i valori ricevuti
Sample samples[NUM_RELE];


ESP8266WebServer server(80);

int rele_pins[NUM_RELE] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37};
bool rele_states[NUM_RELE] = {LOW};

//VARIABILI PER AGGIUNGERE DELAY ALLE API
unsigned long previousMillis = 0;
const long interval = 1000; 
// FINE VARIABILI


void setup(void) {
  for (int i = 0; i < NUM_RELE; i++) {
    pinMode(rele_pins[i], OUTPUT);
    digitalWrite(rele_pins[i], rele_states[i]);
  }



  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
 
  // WiFi connection
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

    Serial.println("");
    Serial.print("esp->Connected to ");
    Serial.println(ssid);
    Serial.print("esp->IP address: ");
    Serial.println(WiFi.localIP());

    // Nuove API
    server.on("/turnOn0", HTTP_GET, [](){
    server.send(200, "text/plain", "all rele turned ON");
    Serial.println("ON0\n");
    previousMillis = millis();  // Salva il tempo corrente
    });

  server.on("/turnOn1", HTTP_GET, [](){
    digitalWrite(rele_pins[1], HIGH);
    rele_states[1] = HIGH;
    server.send(200, "text/plain", "RELE1 turned ON");
    Serial.println("ON1\n");
    previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn2", HTTP_GET, [](){
    digitalWrite(rele_pins[2], HIGH);
    rele_states[2] = HIGH;
    server.send(200, "text/plain", "RELE2 turned ON");
    Serial.println("ON2\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn3", HTTP_GET, [](){
    digitalWrite(rele_pins[3], HIGH);
    rele_states[3] = HIGH;
    server.send(200, "text/plain", "RELE3 turned ON");
    Serial.println("ON3\n");
    previousMillis = millis();  // Salva il tempo corrente
  });

  // Aggiungi le seguenti API per i restanti relè (da 4 a 16)
  server.on("/turnOn4", HTTP_GET, [](){
    digitalWrite(rele_pins[4], HIGH);
    rele_states[4]= HIGH;
    server.send(200, "text/plain", "RELE4 turned ON");
    Serial.println("ON4\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn5", HTTP_GET, [](){
    digitalWrite(rele_pins[5], HIGH);
    rele_states[5] = HIGH;
    server.send(200, "text/plain", "RELE5 turned ON");
    Serial.println("ON5\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  // Nuove API
  server.on("/turnOn6", HTTP_GET, [](){
    digitalWrite(rele_pins[6], HIGH);
    rele_states[6] = HIGH;
    server.send(200, "text/plain", "RELE6 turned ON");
    Serial.println("ON6\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn7", HTTP_GET, [](){
    digitalWrite(rele_pins[7], HIGH);
    rele_states[7] = HIGH;
    server.send(200, "text/plain", "RELE7 turned ON");
    Serial.println("ON7\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn8", HTTP_GET, [](){
    digitalWrite(rele_pins[8], HIGH);
    rele_states[8] = HIGH;
    server.send(200, "text/plain", "RELE8 turned ON");
    Serial.println("ON8\n");
    previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn9", HTTP_GET, [](){
    digitalWrite(rele_pins[9], HIGH);
    rele_states[9] = HIGH;
    server.send(200, "text/plain", "RELE9 turned ON");
    Serial.println("ON9\n");
    previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn10", HTTP_GET, [](){
    digitalWrite(rele_pins[10], HIGH);
    rele_states[10] = HIGH;
    server.send(200, "text/plain", "RELE10 turned ON");
    Serial.println("ON10\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn11", HTTP_GET, [](){
    digitalWrite(rele_pins[11], HIGH);
    rele_states[11] = HIGH;
    server.send(200, "text/plain", "RELE11 turned ON");
    Serial.println("ON11\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn12", HTTP_GET, [](){
    digitalWrite(rele_pins[12], HIGH);
    rele_states[12] = HIGH;
    server.send(200, "text/plain", "RELE12 turned ON");
    Serial.println("ON12\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn13", HTTP_GET, [](){
    digitalWrite(rele_pins[13], HIGH);
    rele_states[13] = HIGH;
    server.send(200, "text/plain", "RELE13 turned ON");
    Serial.println("ON13\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn14", HTTP_GET, [](){
    digitalWrite(rele_pins[14], HIGH);
    rele_states[14] = HIGH;
    server.send(200, "text/plain", "RELE14 turned ON");
    Serial.println("ON14\n");
      previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn15", HTTP_GET, [](){
    digitalWrite(rele_pins[15], HIGH);
    rele_states[15] = HIGH;
    server.send(200, "text/plain", "RELE15 turned ON");
    Serial.println("ON15\n");
    previousMillis = millis();  // Salva il tempo corrente
  });

  server.on("/turnOn16", HTTP_GET, [](){
    digitalWrite(rele_pins[16], HIGH);
    rele_states[16] = HIGH;
    server.send(200, "text/plain", "RELE16 turned ON");
    Serial.println("ON16\n");
      previousMillis = millis();  // Salva il tempo corrente
  });


  // Configura le tue API per ottenere i valori
    server.on("/api/first", HTTP_GET, [](){
      server.send(200, "text/plain", String(voltageMPP));
    });

    server.on("/api/second", HTTP_GET, [](){
      server.send(200, "text/plain", String(currentMPP));
    });

    server.on("/api/third", HTTP_GET, [](){
      server.send(200, "text/plain", String(powerMPP));
    });


  server.on("/get16Values", HTTP_GET, [](){
  DynamicJsonDocument jsonDocument(1024); // Dimensione arbitraria del documento JSON
  JsonArray jsonArray = jsonDocument.createNestedArray("values");  // Aggiunta delle 16 coppie di valori all'oggetto JSON
  for (int i = 0; i < NUM_RELE; ++i) {
    JsonObject jsonSample = jsonArray.createNestedObject();
    jsonSample["voltage"] = samples[i].voltage;
    jsonSample["current"] = samples[i].current;

    // Aggiungi console log per visualizzare i dati di corrente e tensione
    Serial.print("Dati di corrente e tensione del api ");
    Serial.println(i);
    Serial.print("esp->Tensione: ");
    Serial.println(samples[i].voltage);
    Serial.print("esp->Corrente: ");
    Serial.println(samples[i].current);
  }

  // Converti l'oggetto JSON in una stringa
  String jsonString;
  serializeJson(jsonDocument, jsonString);

  // Invia la risposta JSON
  server.send(200, "application/json", jsonString);
});


    server.begin();
    Serial.println("HTTP server started");
  
}

void loop(void) {
  server.handleClient();

  //CODICE PER DELAY API
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // Esegui azioni che devono essere eseguite ogni intervallo
    digitalWrite(rele_pins[1], LOW);
   rele_states[1] = LOW;
    digitalWrite(rele_pins[2], LOW);
   rele_states[2] = LOW;
    // Ripeti per gli altri pin

    // Resetta il tempo
    previousMillis = currentMillis;
  }
  // FINE CODICE PER DELAY API
}


String receivedData = ""; // Stringa per memorizzare i dati ricevuti
int currentIndex = 0; // Indice corrente nell'array di campioni

void serialEvent() {
    while (Serial.available()) {
        char inChar = Serial.read();
        if (inChar == '\n') { // Se il carattere di nuova riga è stato ricevuto, elabora i dati
            processReceivedData(receivedData);
            receivedData = ""; // Resetta la stringa per memorizzare i prossimi dati
            currentIndex = 0; // Resetta l'indice per i prossimi campioni
        } else {
            receivedData += inChar; // Aggiungi il carattere alla stringa dei dati ricevuti
        }
    }
}

void processReceivedData(String data) {
    // Dividi la stringa dei dati in sottostringhe usando lo spazio come delimitatore
    String tokens[NUM_RELE * 2 + 3];
    int numTokens = 0;
    int lastIndex = 0;
    for (int i = 0; i < data.length(); ++i) {
        if (data.charAt(i) == ' ') {
            tokens[numTokens++] = data.substring(lastIndex, i); // Estrai la sottostringa
            lastIndex = i + 1; // Imposta l'indice per il prossimo carattere
        }
    }
    // Se ci sono ancora caratteri rimanenti, aggiungi l'ultima sottostringa
    if (lastIndex < data.length()) {
        tokens[numTokens++] = data.substring(lastIndex);
    }

    // Assegna i primi tre valori a tensioneMPP, correnteMPP e potenzaMPP
    voltageMPP = tokens[0].toFloat();
    currentMPP = tokens[1].toFloat();
    powerMPP = tokens[2].toFloat();

    // Assegna i valori di tensione e corrente ai campioni
    for (int i = 3; i < numTokens; i += 2) {
        samples[currentIndex].voltage = tokens[i].toFloat();
        samples[currentIndex].current = tokens[i + 1].toFloat();
        currentIndex++; // Incrementa l'indice per passare al prossimo campione
    }
}



 
  




