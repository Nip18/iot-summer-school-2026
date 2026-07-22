# Project 9 - Smart Stepper Positioner

## Objective

Develop an Arduino-based position control system that precisely rotates a stepper motor to user-defined positions using a potentiometer and push buttons, while displaying the motor position in real time.

## Components Used

- Arduino Uno
- 28BYJ-48 Stepper Motor
- ULN2003 Stepper Motor Driver
- Potentiometer (10kΩ)
- Push Buttons
- SSD1306 OLED Display (optional)
- Breadboard
- Jumper Wires

## Circuit Connections

| Component | Arduino Pin |
|-----------|-------------|
| ULN2003 IN1 | D8 |
| ULN2003 IN2 | D9 |
| ULN2003 IN3 | D10 |
| ULN2003 IN4 | D11 |
| Potentiometer | A0 |
| Button 1 | D2 |
| Button 2 | D3 |
| OLED SDA | A4 |
| OLED SCL | A5 |

## Libraries Used

- Stepper
- Adafruit GFX
- Adafruit SSD1306
- Wire

## Features

- Precise stepper motor position control
- Potentiometer-based angle selection
- Manual button control
- Real-time OLED display (optional)
- Serial Monitor logging
- Smooth motor movement

## Working Principle

The Arduino reads the potentiometer to determine the desired motor position. Based on the input, it drives the 28BYJ-48 stepper motor through the ULN2003 driver to the target position. Push buttons can also be used for manual positioning. The current motor position is displayed on the OLED display and continuously updated on the Serial Monitor.

## How to Run

1. Connect all components.
2. Upload the Arduino sketch.
3. Rotate the potentiometer or use the push buttons.
4. Observe the stepper motor moving to the selected position.

## Expected Output

- Smooth and accurate stepper motor movement.
- Position updates on the OLED display (optional).
- Real-time Serial Monitor output.
- Responsive manual control using the potentiometer and buttons.

## Folder Structure

```
Project9/
│── Project9.ino
└── README.md
```

## Future Improvements

- Closed-loop position feedback
- Rotary encoder support
- Mobile app control
- Motion profiling with acceleration/deceleration
- Preset position storage