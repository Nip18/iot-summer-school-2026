#include <Servo.h>

int potPin = A0;
int btnPin = 2;
int servoPin = 9;

Servo myServo;

void setup() {
  myServo.attach(servoPin);
  pinMode(btnPin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // Check if button is pressed
  if (digitalRead(btnPin) == LOW) {
    delay(50); // debounce
    if (digitalRead(btnPin) == LOW) {
      
      // Sweep Up
      for (int angle = 0; angle <= 180; angle++) {
        myServo.write(angle);
        Serial.print("Sweep Angle: ");
        Serial.println(angle);
        delay(15);
      }
      
      // Sweep Down
      for (int angle = 180; angle >= 0; angle--) {
        myServo.write(angle);
        Serial.print("Sweep Angle: ");
        Serial.println(angle);
        delay(15);
      }
      
      while(digitalRead(btnPin) == LOW); // Wait for release
    }
  }

  // Regular potentiometer control mode
  int potVal = analogRead(potPin);
  int angleMapped = map(potVal, 0, 1023, 0, 180);
  
  myServo.write(angleMapped);
  
  Serial.print("Potentiometer Angle: ");
  Serial.println(angleMapped);
  
  delay(50); 
}
