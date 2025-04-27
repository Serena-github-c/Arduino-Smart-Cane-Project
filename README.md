# Arduino Smart Cane Project

**Smart Cane for Visually Impaired:**  
An Arduino-based assistive device that uses ultrasonic sensors to detect nearby obstacles and water puddles.  
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
- 📸 **Camera Emergency Snapshot** *(easy if ESP32-CAM used)*
- 📏 **Obstacle Height Detection**

---

## 🛠️ Components List

| # | Component Name | Quantity |
|---|----------------|----------|
| 1 | ESP32-WROOM-32 Development Board | 1 |
| 2 | HC-SR04 Ultrasonic Sensors | 5 |
| 3 | Mini Vibration Motor (3V–5V) | 1 |
| 4 | DFPlayer Mini MP3 Player Module | 1 |
| 5 | MicroSD Card (≤8GB, FAT32) | 1 |
| 6 | 3W 4Ω Mini Speaker | 1 |
| 7 | LDR Sensor (Light Dependent Resistor) | 1 |
| 8 | 5V White High-Brightness LED | 1 |
| 9 | NPN Transistor (e.g., 2N2222) | 1 |
| 10 | 10kΩ Resistors | 10 |
| 11 | 4.7kΩ Resistors | 5 |
| 12 | Flyback Diode (e.g., 1N4007) | 1 |
| 13 | SIM800L GSM Module | 1 |
| 14 | NEO-6M GPS Module | 1 |
| 15 | Tactile Push Button | 1 |
| 16 | Electrolytic Capacitor (470µF 16V) | 1 |
| 17 | YL-83 Water Sensor Module (or FC-37) | 1 |
| 18 | HMC5883L Digital Compass Module | 1 |
| 19 | 18650 Li-ion Rechargeable Batteries (3.7V 2000–3000mAh) | 2 |
| 20 | TP4056 Battery Charging Module (with Protection) | 1 |
| 21 | MT3608 Boost Converter (Step-Up 5V Module) | 1 |
| 22 | FTDI USB-to-TTL Module (CP2102) | 1 |
| 23 | Jumper Wires (Male-Female, Male-Male, Female-Female) | Bunch of each type |
| 24 | Slide Switch | 1 |

---

## 📜 Notes
- ⚡ **Voltage Protection:** Use resistor dividers (10kΩ and 4.7kΩ) for HC-SR04 Echo pins to protect ESP32.
- 🛡️ **Motor Protection:** Use a flyback diode (1N4007) across the vibration motor.
- 🔋 **Power Management:** Batteries are charged using a TP4056 module and boosted to 5V via an MT3608 converter.
- 🖥️ **Programming:** Use the FTDI USB-to-TTL adapter for initial code uploading to the ESP32.

---

