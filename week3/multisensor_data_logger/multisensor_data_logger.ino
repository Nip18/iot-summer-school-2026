#include "DHT.h"

int dhtPin = 2;
int trigPin = 3;
int echoPin = 4;
int ldrPin = A0;

unsigned long lastLogTime = 0;

DHT dht(dhtPin, DHT11);

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastLogTime >= 5000) {
    lastLogTime = currentMillis;

    float humidity = dht.readHumidity();
    float temp = dht.readTemperature();

    int rawLDR = analogRead(ldrPin);
    int lightPercent = map(rawLDR, 0, 1023, 0, 100); 
    
    String lightStatus;
    if (lightPercent < 30)       lightStatus = "Dark";
    else if (lightPercent < 70)  lightStatus = "Dim";
    else                         lightStatus = "Bright";

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    long duration = pulseIn(echoPin, HIGH);
    int distance = (duration * 0.034) / 2; 

    Serial.println("=== SENSOR LOG ===");
    
    Serial.print("Time     : ");
    Serial.print(currentMillis);
    Serial.println(" ms");
    
    Serial.print("Temp     : ");
    Serial.print(temp, 1);
    Serial.print(" C | Humidity: ");
    Serial.print(humidity, 0);
    Serial.println("%");
    
    Serial.print("Light    : ");
    Serial.print(lightPercent);
    Serial.print("% (");
    Serial.print(lightStatus);
    Serial.println(")");
    
    Serial.print("Distance : ");
    Serial.print(distance);
    Serial.println(" cm");
    
    Serial.println("==================");
  }
}
