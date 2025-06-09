# Arduino Smart Cane Project

**Smart Cane for Visually Impaired:**  
An Arduino Mega 2560-based assistive device that uses ultrasonic sensors to detect nearby obstacles and water puddles.  
It provides real-time feedback through **vibrations** and a **buzzer**.  
The system also uses a **speaker** to read alerts aloud and integrates **GPS** for location tracking and **navigation assistance**.

---

## 🚀 Features
- 🔵 **Obstacle Avoidance + Vibration Feedback**
- 🎤 **Voice-Assisted Navigation**
- 🌙 **Automatic Nighttime Lighting**
- 🆘 **Emergency Button + SMS + Location Sharing**
- 💧 **Water Detection**
- 🧭 **Compass / Direction Guidance**

---

## 🚧 Potential Future Features
- 🔋 **Battery Low Alert** *(easy to implement)*
- 🚑 **Fall Detection** *(needs more work)*
- 📏 **Obstacle Height Detection**

---

## 🛠️ Components List

| # | Component Name | Quantity | Function | 
|---|----------------|----------|---------- |  
| 1 | Arduino Mega 2560 | 1 |  Acts as the main controller of the system. Manages sensors, processes input, and controls output via digital and analog I/O pins. |
| 2 | HC-SR04 Ultrasonic Sensors | 5 | Detects nearby obstacles: sends sound pulse, measures echo return time, calculates distance |
|---|----------------|----------|---------- | 
| 3 | Mini Vibration Motor (3V–5V) | 1 | - Provides tactile feedback when obstacle detected |
| 4 | DFPlayer Mini MP3 Player Module | 1 |  Plays pre-recorded voice messages |
| 5 | MicroSD Card (≤8GB, FAT32) | 1 | Stores MP3 audio files for voice feedback. |
| 6 | 3W 4Ω Mini Speaker | 1 | Outputs audible voice alerts. |
| 7 | LDR Sensor (Light Dependent Resistor) | 1 | Detects ambient light levels  |
| 8 | 5V White High-Brightness LED | 1 | Lights up automatically in low-light conditions  |
| 9 | NPN Transistor (e.g., 2N2222) | 1 | Acts as a switch for LED and Vibration motor  |
| 10 | 10kΩ Resistors | 10 | Used for voltage dividers and pull-downs. |
| 11 | 4.7kΩ Resistors | 5 | Used for voltage dividers and pull-downs. |
| 12 | Flyback Diode (e.g., 1N4007) | 1 | Protects circuits from motor back-EMF.  |
|---|----------------|----------|---------- | 
| 13 | SIM800L GSM Module | 1 | Sends emergency SMS containing GPS coordinates.  |
| 14 | NEO-6M GPS Module | 1 | Provides real-time location data. |
| 15 | Tactile Push Button | 1 | Emergency alert trigger. |
| 16 | Electrolytic Capacitor (470µF 16V) | 1 | Stabilizes power supply.  |
|---|----------------|----------|---------- | 
| 17 | YL-83 Water Sensor Module (or FC-37) | 1 | Detects water puddles.  |
| 18 | HMC5883L Digital Compass Module | 1 | Guides direction (North, East, South, West). |
|---|----------------|----------|---------- | 
| 19 | 18650 Li-ion Rechargeable Batteries (3.7V 2000–3000mAh) | 2 | Main portable power source. |
| 20 | TP4056 Battery Charging Module (with Protection) | 1 | Charges 18650 safely via USB. |
| 21 | MT3608 Boost Converter (Step-Up 5V Module) | 1 | Boosts battery voltage to stable 5V. |
| 22 | USB Type-B Cable | 1 | Used to upload code directly to the Arduino Mega 2560 via USB. |
| 23 | Jumper Wires (Male-Female, Male-Male, Female-Female) | Bunch of each type |
| 24 | Slide Switch | 1 | Manually turns the smart cane on or off. |
|---|----------------|----------|---------- | 
---

## 📜 Notes
- ⚡ **Voltage Protection:** Use resistor dividers (10kΩ and 4.7kΩ) for HC-SR04 Echo pins to protect Arduino Mega 2560 digital pins.
- 🛡️ **Motor Protection:** Use a flyback diode (1N4007) across the vibration motor.
- 🔋 **Power Management:** Batteries are charged using a TP4056 module and boosted to 5V via an MT3608 converter.
- 🖥️ **Programming:** Use a USB Type-B cable to upload the code directly to the Arduino Mega 2560 using the Arduino IDE.

---

## 👥 Contributors

This project was collaboratively developed by:

- [@Ali-ghassan-yazbeck](https://github.com/Ali-ghassan-yazbeck)
- [@Serena-github-c](https://github.com/Serena-github-c)     
- [@zeinattar](https://github.com/zeinattar)

All three contributors are engineering students who worked together on system design, code development, hardware integration, and documentation.
