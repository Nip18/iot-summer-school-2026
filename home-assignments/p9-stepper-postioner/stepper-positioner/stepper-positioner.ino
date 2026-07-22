/*
===========================================================
 IIT Jammu Summer School 2026
 Project 9 : Stepper Motor Precision Positioner
===========================================================
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Stepper.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//------------------------------------------------------
// Stepper
//------------------------------------------------------

const int STEPS_PER_REV = 4096;

Stepper stepper(
  STEPS_PER_REV,
  8,
  9,
  10,
  11
);

//------------------------------------------------------
// Pins
//------------------------------------------------------

const int POT_PIN = A0;

const int BTN_CW   = 2;
const int BTN_CCW  = 3;
const int BTN_HOME = 4;

//------------------------------------------------------
// Variables
//------------------------------------------------------

long currentSteps = 0;
long targetSteps  = 0;

float currentAngle = 0;
float targetAngle  = 0;

String directionText = "STOP";

unsigned long lastOLED = 0;
unsigned long lastSerial = 0;

const unsigned long OLED_INTERVAL = 200;
const unsigned long SERIAL_INTERVAL = 1000;

//------------------------------------------------------
// Debounce
//------------------------------------------------------

bool lastCW = HIGH;
bool lastCCW = HIGH;
bool lastHOME = HIGH;

unsigned long debounceCW = 0;
unsigned long debounceCCW = 0;
unsigned long debounceHOME = 0;

const int debounceDelay = 50;

//------------------------------------------------------
// Function Prototypes
//------------------------------------------------------

void readPot();
void checkButtons();
void moveMotor();
void updateOLED();
void printSerial();

//------------------------------------------------------
// Setup
//------------------------------------------------------

void setup()
{
    Serial.begin(9600);

    pinMode(BTN_CW, INPUT_PULLUP);
    pinMode(BTN_CCW, INPUT_PULLUP);
    pinMode(BTN_HOME, INPUT_PULLUP);

    stepper.setSpeed(12);

    if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C))
    {
        Serial.println("OLED Failed");

        while(1);
    }

    display.clearDisplay();

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(12,18);
    display.println("Project 9");

    display.setCursor(0,35);
    display.println("Stepper Positioner");

    display.display();

    delay(2000);

    display.clearDisplay();
    display.display();
}

//------------------------------------------------------
// Potentiometer
//------------------------------------------------------

void readPot()
{
    int value = analogRead(POT_PIN);

    targetAngle = (value / 1023.0) * 360.0;

    targetSteps = (targetAngle / 360.0) * STEPS_PER_REV;
}

//------------------------------------------------------
// Buttons
//------------------------------------------------------

void checkButtons()
{

    bool cw = digitalRead(BTN_CW);
    bool ccw = digitalRead(BTN_CCW);
    bool home = digitalRead(BTN_HOME);

    //---------------- CW ----------------

    if(cw != lastCW)
        debounceCW = millis();

    if((millis()-debounceCW)>debounceDelay)
    {
        if(lastCW==HIGH && cw==LOW)
        {
            targetSteps += 512;

            if(targetSteps>STEPS_PER_REV)
                targetSteps = STEPS_PER_REV;

            targetAngle =
            (targetSteps*360.0)/STEPS_PER_REV;
        }
    }

    lastCW = cw;

    //---------------- CCW ----------------

    if(ccw != lastCCW)
        debounceCCW = millis();

    if((millis()-debounceCCW)>debounceDelay)
    {
        if(lastCCW==HIGH && ccw==LOW)
        {
            targetSteps -= 512;

            if(targetSteps<0)
                targetSteps = 0;

            targetAngle =
            (targetSteps*360.0)/STEPS_PER_REV;
        }
    }

    lastCCW = ccw;

    //---------------- HOME ----------------

    if(home != lastHOME)
        debounceHOME = millis();

    if((millis()-debounceHOME)>debounceDelay)
    {
        if(lastHOME==HIGH && home==LOW)
        {
            targetSteps = 0;
            targetAngle = 0;
        }
    }

    lastHOME = home;
}

//------------------------------------------------------
// Motor Movement
//------------------------------------------------------

void moveMotor()
{

    if(currentSteps < targetSteps)
    {
        stepper.step(1);

        currentSteps++;

        directionText = "CW";
    }

    else if(currentSteps > targetSteps)
    {
        stepper.step(-1);

        currentSteps--;

        directionText = "CCW";
    }

    else
    {
        directionText = "STOP";
    }

    currentAngle =
    (currentSteps * 360.0) / STEPS_PER_REV;
}

//------------------------------------------------------
// OLED
//------------------------------------------------------

void updateOLED()
{

    display.clearDisplay();

    display.setTextSize(1);

    display.setCursor(0,0);
    display.print("Current : ");
    display.print(currentAngle,1);
    display.println((char)247);

    display.setCursor(0,16);
    display.print("Target  : ");
    display.print(targetAngle,1);
    display.println((char)247);

    display.setCursor(0,32);
    display.print("Dir     : ");
    display.println(directionText);

    display.setCursor(0,48);
    display.print("Steps   : ");
    display.print(currentSteps);

    display.display();
}

//------------------------------------------------------
// Serial Monitor
//------------------------------------------------------

void printSerial()
{

    Serial.print("Current = ");
    Serial.print(currentAngle,1);

    Serial.print(" deg | Target = ");
    Serial.print(targetAngle,1);

    Serial.print(" deg | Dir = ");
    Serial.print(directionText);

    Serial.print(" | Steps = ");
    Serial.println(currentSteps);

}

//------------------------------------------------------
// Main Loop
//------------------------------------------------------

void loop()
{

    readPot();

    checkButtons();

    moveMotor();

    if(millis() - lastOLED >= OLED_INTERVAL)
    {
        lastOLED = millis();
        updateOLED();
    }

    if(millis() - lastSerial >= SERIAL_INTERVAL)
    {
        lastSerial = millis();
        printSerial();
    }

}