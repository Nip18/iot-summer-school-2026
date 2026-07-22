// Project 2: Gas & Fire Safety Alert System

const int mq2Pin = A0;
const int flamePin = 7;

const int greenLED = 10;
const int yellowLED = 11;
const int redLED = 12;

const int buzzer = 9;

unsigned long previousMillis = 0;
bool buzzerState = false;

void setup() {

  Serial.begin(9600);

  pinMode(flamePin, INPUT_PULLUP);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

}

void loop() {

  int gasValue = analogRead(mq2Pin);

  int gasPercent = map(gasValue, 0, 1023, 0, 100);

  bool flameDetected = (digitalRead(flamePin) == LOW);

  if (gasPercent > 60 || flameDetected) {

    dangerState(gasPercent, flameDetected);

  }

  else if (gasPercent >= 30) {

    warningState(gasPercent);

  }

  else {

    safeState(gasPercent);

  }

  delay(100);

}

void safeState(int gas) {

  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, LOW);

  noTone(buzzer);

  Serial.print("Gas: ");
  Serial.print(gas);
  Serial.println("% | Flame: NO | STATUS: SAFE");

}

void warningState(int gas) {

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, HIGH);
  digitalWrite(redLED, LOW);

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 500) {

    previousMillis = currentMillis;

    buzzerState = !buzzerState;

    if (buzzerState)
      tone(buzzer, 1000);
    else
      noTone(buzzer);

  }

  Serial.print("Gas: ");
  Serial.print(gas);
  Serial.println("% | Flame: NO | STATUS: WARNING");

}

void dangerState(int gas, bool flame) {

  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
  digitalWrite(redLED, HIGH);

  tone(buzzer, 1500);

  Serial.print("Gas: ");
  Serial.print(gas);
  Serial.print("% | Flame: ");

  if (flame)
    Serial.print("YES");
  else
    Serial.print("NO");

  Serial.println(" | STATUS: DANGER");

}