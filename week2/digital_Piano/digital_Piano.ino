const int BUZZER_PIN = 11;
const int BUTTON_DO = 2;
const int BUTTON_RE = 3;
const int BUTTON_MI = 4;
const int BUTTON_FA = 5;

// basic frequencies for major scale notes(fetched)
const int scaleNotes[] = {262, 294, 330, 349}; 

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_DO, INPUT_PULLUP);
  pinMode(BUTTON_RE, INPUT_PULLUP);
  pinMode(BUTTON_MI, INPUT_PULLUP);
  pinMode(BUTTON_FA, INPUT_PULLUP);
}

void loop() {
  bool pressDo = (digitalRead(BUTTON_DO) == LOW);
  bool pressRe = (digitalRead(BUTTON_RE) == LOW);
  bool pressMi = (digitalRead(BUTTON_MI) == LOW);
  bool pressFa = (digitalRead(BUTTON_FA) == LOW);

  // check if two or more buttons are pressed simultaneously
  int pressedCount = pressDo + pressRe + pressMi + pressFa;

  if (pressedCount >= 2) {
    tone(BUZZER_PIN, 392); // play Sol (392Hz) as a chord substitute
  } else if (pressDo) {
    tone(BUZZER_PIN, 262);
  } else if (pressRe) {
    tone(BUZZER_PIN, 294);
  } else if (pressMi) {
    tone(BUZZER_PIN, 330);
  } else if (pressFa) {
    tone(BUZZER_PIN, 349);
  } else {
    noTone(BUZZER_PIN);
  }
}
