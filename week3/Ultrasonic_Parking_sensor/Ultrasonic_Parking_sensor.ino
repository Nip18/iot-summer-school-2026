int trigPin = 3;
int echoPin = 4;
int ledYellow = 5;
int ledRed = 6;
int buzzerPin = 7;

unsigned long lastBuzzerTime = 0;
bool buzzerState = false;

unsigned long lastFlashTime = 0;
bool flashState = false;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  // Trigger HC-SR04 sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = (duration * 0.034) / 2.0;

  // Mode 1: SAFE
  if (distance > 50.0) {
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    noTone(buzzerPin);
    Serial.println("SAFE");
  } 
  
  // Mode 2: Warning Zone (500ms beeps)
  else if (distance >= 20.0 && distance <= 50.0) {
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    
    if (currentTime - lastBuzzerTime >= 500) {
      lastBuzzerTime = currentTime;
      buzzerState = !buzzerState;
      if (buzzerState) tone(buzzerPin, 1000);
      else noTone(buzzerPin);
    }
  } 
  
  // Mode 3: Critical Zone (200ms beeps)
  else if (distance >= 10.0 && distance < 20.0) {
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    
    if (currentTime - lastBuzzerTime >= 200) {
      lastBuzzerTime = currentTime;
      buzzerState = !buzzerState;
      if (buzzerState) tone(buzzerPin, 1000);
      else noTone(buzzerPin);
    }
  } 
  
  // Mode 4: Danger Zone (Rapid flashing + continuous buzzer)
  else if (distance < 10.0) {
    tone(buzzerPin, 1000); 
    
    if (currentTime - lastFlashTime >= 100) {
      lastFlashTime = currentTime;
      flashState = !flashState;
      digitalWrite(ledYellow, flashState);
      digitalWrite(ledRed, !flashState);
    }
  }

  // Display distance on Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  delay(60); // Small stability delay between sensor readings
}
