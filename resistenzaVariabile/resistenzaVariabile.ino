#include <Wire.h>
#include "Adafruit_INA219.h"

Adafruit_INA219 ina219;

const int minResistance = 0;       // Resistenza minima (ohm)
const int maxResistance = 10000;    // Resistenza massima (ohm)
const int numSteps = 100;           // Numero di passi di variazione della resistenza
const unsigned long stepDuration = 200; // Durata di ciascun passo (millisecondi)

bool processStarted = false;
unsigned long previousMillis = 0;
int currentResistance = minResistance;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // attendere che la porta seriale si connetta. Necessario solo per le schede native USB
  }
  
  ina219.begin();
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.equals("inizia")) {
      processStarted = true;
      previousMillis = millis(); // Resetta il timer
    }
  }

  if (processStarted) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= stepDuration) {
      previousMillis = currentMillis;

      float shuntVoltage = ina219.getShuntVoltage_mV();
      float busVoltage = ina219.getBusVoltage_V();
      float current_mA = ina219.getCurrent_mA();
      float loadVoltage = busVoltage + (shuntVoltage / 1000);

      Serial.print("Resistenza (Ohm) = ");
      Serial.print(currentResistance);
      Serial.print(", Tensione = ");
      Serial.print(loadVoltage);
      Serial.print(" V, Corrente = ");
      Serial.print(current_mA);
      Serial.println(" mA");

      currentResistance += (maxResistance - minResistance) / numSteps; // Incrementa la resistenza per il prossimo passo

      if (currentResistance > maxResistance) {
        Serial.println("Resistenza massima raggiunta. Fine del programma.");
        processStarted = false; // Imposta il flag per indicare il completamento del processo
      }
    }
  }
}
