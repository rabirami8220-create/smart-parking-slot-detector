# Smart Parking Slot Detector

An Arduino Uno IoT prototype, simulated in Wokwi, that detects free and occupied parking slots and controls an entry gate.

## Features
- 2 ultrasonic sensors (HC-SR04) detect vehicles: occupied if distance is under 20 cm
- Green and red LEDs show each slot's status
- I2C LCD shows the number of free slots
- Servo gate opens only when a slot is free
- Buzzer alerts when the lot is full

## Components
Arduino Uno, 2x HC-SR04, 2x green LED, 2x red LED, 4x 220 ohm resistor, I2C LCD 16x2, servo motor, buzzer

## Pin Connections
| Device | Pin |
|---|---|
| Slot 1 TRIG / ECHO | 9 / 10 |
| Slot 1 green / red LED | 6 / 7 |
| Slot 2 TRIG / ECHO | 11 / 12 |
| Slot 2 green / red LED | 4 / 5 |
| Servo | 3 |
| Buzzer | 8 |
| LCD SDA / SCL | A4 / A5 |

## Live Simulation
Wokwi:https://wokwi.com/projects/479572099009632257

## Files
- `sketch.ino`: Arduino code
- `diagram.json`: Wokwi circuit
- Screenshots of the working prototype

## Limitations
Simulation only, 2 slots, no internet connectivity.

## Future Scope
ESP32 with MQTT dashboard, mobile app, RFID entry.
