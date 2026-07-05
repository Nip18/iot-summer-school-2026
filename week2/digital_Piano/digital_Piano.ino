const int BUZZER_PIN = 11;
const int BUTTON_DO = 2;
const int BUTTON_RE = 3;
const int BUTTON_MI = 4;
const int BUTTON_FA = 5;
const int TOGGLE_MODE_PIN = 6;

// frequencies: Do, Re, Mi, Fa, Sol
const int majorScale[] = {262, 294, 330, 349, 392}; 
const int minorScale[] = {262, 294, 311, 349, 392}; // Mi-flat at 311Hz for minor

bool isMajorMode = true;
bool lastToggleState = HIGH;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_DO, INPUT_PULLUP);
  pinMode(BUTTON_RE, INPUT_PULLUP);
  pinMode(BUTTON_MI, INPUT_PULLUP);
  pinMode(BUTTON_FA, INPUT_PULLUP);
  pinMode(TOGGLE_MODE_PIN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // read and debounce scale toggle button state
  bool currentToggleState = digitalRead(TOGGLE_MODE_PIN);
  if (currentToggleState == LOW && lastToggleState == HIGH) {
    delay(50); // software debouncing window
    if (digitalRead(TOGGLE_MODE_PIN) == LOW) {
      isMajorMode = !isMajorMode;
      Serial.print("Active Scale: ");
      Serial.println(isMajorMode ? "MAJOR" : "MINOR");
    }
  }
  lastToggleState = currentToggleState;

  bool pressDo = (digitalRead(BUTTON_DO) == LOW);
  bool pressRe = (digitalRead(BUTTON_RE) == LOW);
  bool pressMi = (digitalRead(BUTTON_MI) == LOW);
  bool pressFa = (digitalRead(BUTTON_FA) == LOW);

  int pressedCount = pressDo + pressRe + pressMi + pressFa;
  const int* activeScale = isMajorMode ? majorScale : minorScale;

  if (pressedCount >= 2) {
    tone(BUZZER_PIN, activeScale[4]); // Sol chord note
  } else if (pressDo) {
    tone(BUZZER_PIN, activeScale[0]);
  } else if (pressRe) {
    tone(BUZZER_PIN, activeScale[1]);
  } else if (pressMi) {
    tone(BUZZER_PIN, activeScale[2]);
  } else if (pressFa) {
    tone(BUZZER_PIN, activeScale[3]);
  } else {
    noTone(BUZZER_PIN);
  }
}
