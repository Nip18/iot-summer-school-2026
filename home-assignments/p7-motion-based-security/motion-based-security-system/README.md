# Project 7 - Motion-Based Security System

## Objective

Develop an Arduino-based security system that detects human motion using a PIR sensor and alerts the user through LEDs, a buzzer, and the Serial Monitor.

## Components Used

- Arduino Uno
- PIR Motion Sensor
- Green LED
- Red LED
- Active Buzzer
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| PIR Output | D2 |
| Green LED | D8 |
| Red LED | D9 |
| Buzzer | D10 |

## Libraries Used

- None

## Features

- Motion detection
- Intrusion alert
- LED status indication
- Audible alarm
- Real-time Serial Monitor updates
- Low-power operation

## Working Principle

The PIR sensor continuously monitors infrared radiation in its surroundings. When human motion is detected, the sensor output changes, prompting the Arduino to activate the buzzer and red LED while displaying an alert on the Serial Monitor. In the absence of motion, the system remains in monitoring mode with the green LED indicating normal operation.

## How to Run

1. Connect all components.
2. Upload the Arduino sketch.
3. Allow the PIR sensor to stabilize for a few seconds.
4. Move in front of the sensor to trigger the alarm.

## Expected Output

- Green LED indicates monitoring mode.
- Red LED and buzzer activate upon motion detection.
- Motion events are displayed on the Serial Monitor.

## Folder Structure

```
Project7/
│── Project7.ino
└── README.md
```

## Future Improvements

- GSM/SMS alerts
- Wi-Fi notifications
- Camera integration
- Image capture on motion detection
- Cloud-based security monitoring