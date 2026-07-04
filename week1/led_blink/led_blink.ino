/*
 * Project: Variable Speed LED Blink with Telemetry
 * Author: Nipun Pandkar
 * Date: July 2026
 * Description: Reads an analog potentiometer input to adjust LED blinking 
 * frequency while tracking execution iterations via Serial.
 */
int blinkCount = 0;
const int potPin = A0;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(potPin); // Reads values from 0 to 1023
  
  digitalWrite(13, HIGH);
  delay(sensorValue);
  digitalWrite(13, LOW);
  delay(sensorValue);
  
  blinkCount++;
  Serial.print("Blink count: ");
  Serial.println(blinkCount);
}
