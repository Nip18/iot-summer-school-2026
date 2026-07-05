int enA = 5; 
int in1 = 7;
int in2 = 8;
int potPin = A0;
int btnDir = 2;   
int btnStart = 3; 

bool isRunning = false;
bool isForward = true;
int lastSpeedPercent = -1;
bool lastState = false;
bool lastDir = true;

void setup() {
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(btnDir, INPUT_PULLUP);
  pinMode(btnStart, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void loop() {
  int potReading = analogRead(potPin);
  int pwmValue = map(potReading, 0, 1023, 0, 255);
  int speedPercent = map(potReading, 0, 1023, 0, 100);

  if (digitalRead(btnStart) == LOW) {
    delay(200); 
    isRunning = !isRunning;
    while(digitalRead(btnStart) == LOW);
  }

  if (digitalRead(btnDir) == LOW) {
    delay(200); 
    isForward = !isForward;
    while(digitalRead(btnDir) == LOW);
  }

  if (isRunning) {
    if (isForward) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
    analogWrite(enA, pwmValue);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(enA, 0);
  }

  if (speedPercent != lastSpeedPercent || isRunning != lastState || isForward != lastDir) {
    Serial.print("State: ");
    Serial.print(isRunning ? "RUNNING" : "STOPPED");
    Serial.print(" | Direction: ");
    Serial.print(isForward ? "Forward" : "Reverse");
    Serial.print(" | Speed: ");
    Serial.print(speedPercent);
    Serial.println("%");
    
    lastSpeedPercent = speedPercent;
    lastState = isRunning;
    lastDir = isForward;
  }
  
  delay(50);
}
