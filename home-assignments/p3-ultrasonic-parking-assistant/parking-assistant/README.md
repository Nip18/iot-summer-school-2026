# Project 3 - Smart Parking Assistant

## Objective

Develop an ultrasonic sensor-based parking assistance system that measures the distance between a vehicle and nearby obstacles, providing visual and audible feedback to assist in safe parking.

## Components Used

- Arduino Uno
- HC-SR04 Ultrasonic Sensor
- SSD1306 OLED Display (optional)
- Green LED
- Yellow LED
- Red LED
- Active Buzzer
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| HC-SR04 Trig | D9 |
| HC-SR04 Echo | D10 |
| Green LED | D4 |
| Yellow LED | D5 |
| Red LED | D6 |
| Buzzer | D7 |
| OLED SDA | A4 |
| OLED SCL | A5 |

## Libraries Used

- Adafruit GFX
- Adafruit SSD1306

## Features

- Real-time distance measurement
- Three-zone obstacle detection
- LED-based parking guidance
- Audible proximity warning
- OLED distance display (optional)
- Serial Monitor output

## Working Principle

The HC-SR04 ultrasonic sensor continuously measures the distance to nearby objects. Based on predefined distance thresholds, the Arduino classifies the obstacle as Safe, Caution, or Stop. LEDs and the buzzer provide immediate feedback, while the measured distance is displayed on the OLED display and Serial Monitor.

## How to Run

1. Connect all components.
2. Upload the Arduino sketch.
3. Open the Serial Monitor.
4. Move an object closer to the ultrasonic sensor and observe the changing alerts.

## Expected Output

- Live distance measurement.
- Green LED when the obstacle is far away.
- Yellow LED when approaching an obstacle.
- Red LED and buzzer when the obstacle is too close.
- OLED displays the measured distance (optional).

## Folder Structure

```
Project3/
│── Project3.ino
└── README.md
```

## Future Improvements

- LCD display support
- Voice-based parking guidance
- Bluetooth monitoring
- Mobile application integration
- Automatic parking assistance