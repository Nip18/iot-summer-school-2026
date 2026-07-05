#include "DHT.h"

int dhtPin = 2;
int ledRed = 8;
int ledGreen = 9;

unsigned long lastTime = 0; 

// Initialize the sensor (DHT11 type)
DHT dht(dhtPin, DHT11);

void setup() {
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  
  Serial.begin(9600);
  dht.begin();
  
  // Print the required CSV header layout
  Serial.println("timestamp,temp_C,temp_F,humidity");
}

void loop() {
  unsigned long currentTime = millis();

  // Check if 2 seconds (2000 ms) have passed
  if (currentTime - lastTime >= 2000) {
    lastTime = currentTime;

    float humidity = dht.readHumidity();
    float tempC = dht.readTemperature();    
    float tempF = dht.readTemperature(true);

    // Check if the sensor failed to read
    if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
      Serial.println("Error reading from DHT sensor!");
      return; 
    }

    Serial.print(currentTime);
    Serial.print(",");
    Serial.print(tempC, 1);
    Serial.print(",");
    Serial.print(tempF, 1);
    Serial.print(",");
    Serial.println(humidity, 1);

    // Check conditions for LEDs
    if (tempC > 35.0 || humidity > 80.0) {
      digitalWrite(ledRed, HIGH);  
      digitalWrite(ledGreen, LOW);  
    } else {
      digitalWrite(ledRed, LOW);   
      digitalWrite(ledGreen, HIGH);
    }
  }
}
