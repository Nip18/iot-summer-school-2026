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
  if (digitalRead(BUTTON_DO) == LOW) {
    tone(BUZZER_PIN, scaleNotes[0]);
  } else if (digitalRead(BUTTON_RE) == LOW) {
    tone(BUZZER_PIN, scaleNotes[1]);
  } else if (digitalRead(BUTTON_MI) == LOW) {
    tone(BUZZER_PIN, scaleNotes[2]);
  } else if (digitalRead(BUTTON_FA) == LOW) {
    tone(BUZZER_PIN, scaleNotes[3]);
  } else {
    noTone(BUZZER_PIN); // silence the buzzer when released
  }
}
