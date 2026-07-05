const int TARGET_LED = LED_BUILTIN; 
int globalBlinkCounter = 0;

void setup() {
  pinMode(TARGET_LED, OUTPUT);
  digitalWrite(TARGET_LED, LOW);
  Serial.begin(9600);
  Serial.println("System Initialized. Awaiting hardware commands...");
}

void loop() {
  if (Serial.available() > 0) {
    String inputBuffer = Serial.readStringUntil('\n');
    inputBuffer.trim(); // strip the white space/newlines
    
    if (inputBuffer.length() == 0) return;

    if (inputBuffer == "LED_ON") {
      digitalWrite(TARGET_LED, HIGH);
      Serial.println("SUCCESS: Target Built-in LED enabled.");
    } 
    else if (inputBuffer == "LED_OFF") {
      digitalWrite(TARGET_LED, LOW);
      Serial.println("SUCCESS: Target Built-in LED disabled.");
    } 
    else if (inputBuffer.startsWith("BLINK_")) {
      // substrng all the data extraction processing
      String digitSegment = inputBuffer.substring(6);
      int parseCount = digitSegment.toInt();

      // enforce rigid string formatting constraints
      if (parseCount >= 1 && parseCount <= 9 && digitSegment.length() == 1) {
        Serial.print("SUCCESS: Initiating blink routine times = ");
        Serial.println(parseCount);
        
        for (int i = 0; i < parseCount; i++) {
          digitalWrite(TARGET_LED, HIGH);
          delay(200);
          digitalWrite(TARGET_LED, LOW);
          delay(200);
          globalBlinkCounter++;
        }
      } else {
        Serial.println("ERROR: Unknown command");
      }
    } 
    else if (inputBuffer == "STATUS") {
      Serial.println("----- HARDWARE SYSTEM STATUS -----");
      Serial.print("LED Pin State       : ");
      Serial.println(digitalRead(TARGET_LED) == HIGH ? "ON" : "OFF");
      Serial.print("Accumulated Blinks  : ");
      Serial.println(globalBlinkCounter);
      Serial.end(); // clear the port constraints temporarily
      Serial.begin(9600);
    } 
    else if (inputBuffer == "RESET") {
      globalBlinkCounter = 0;
      Serial.println("SUCCESS: Resetting master telemetry tracking counters.");
    } 
    else {
      Serial.println("ERROR: Unknown command");
    }
  }
}
