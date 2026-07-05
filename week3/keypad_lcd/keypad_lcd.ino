#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int ledGreen = 10;
int ledRed = 11;
int buzzer = 12;

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

String correctPIN = "1234";
String inputPIN = "";
int wrongAttempts = 0;
bool lockedOut = false;
unsigned long lockoutTime = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  resetUI();
}

void loop() {
  unsigned long currentTime = millis();

  if (lockedOut) {
    unsigned long remaining = (10000 - (currentTime - lockoutTime)) / 1000;
    lcd.setCursor(0, 1);
    lcd.print("Locked: "); lcd.print(remaining); lcd.print("s   ");
    
    if (currentTime - lockoutTime >= 10000) {
      lockedOut = false;
      wrongAttempts = 0;
      resetUI();
    }
    return; 
  }

  char key = customKeypad.getKey();
  
  if (key) {
    if (key == '#') {
      if (inputPIN == correctPIN) {
        lcd.clear();
        lcd.print("ACCESS GRANTED");
        digitalWrite(ledGreen, HIGH);
        tone(buzzer, 1000, 500);
        delay(3000);
        wrongAttempts = 0;
        resetUI();
      } else {
        wrongAttempts++;
        lcd.clear();
        lcd.print("ACCESS DENIED");
        digitalWrite(ledRed, HIGH);
        tone(buzzer, 400, 500);
        delay(1500);
        
        if (wrongAttempts >= 3) {
          lockedOut = true;
          lockoutTime = millis();
          lcd.clear();
          lcd.print("LOCKED OUT!");
        } else {
          resetUI();
        }
      }
    } 
    else if (key == '*') {
      inputPIN = "";
      lcd.setCursor(0, 1);
      lcd.print("                ");
    } 
    else if (inputPIN.length() < 4) {
      inputPIN += key;
      lcd.setCursor(inputPIN.length() - 1, 1);
      lcd.print('*'); 
    }
  }
}

void resetUI() {
  lcd.clear();
  lcd.print("ENTER PIN:");
  inputPIN = "";
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
  noTone(buzzer);
}
