# Arduino Smart Cane Project

**Smart Cane for Visually Impaired:**  
An Arduino Mega 2560-based assistive device that uses ultrasonic sensors to detect nearby obstacles and water puddles.  
It provides real-time feedback through **vibrations** and a **buzzer**.  
The system also uses a **speaker** to read alerts aloud and integrates **GPS** for location tracking and **navigation assistance**.

---

## 🚀 Features
- 🔵 **Obstacle Detection**
- 🎤 **Voice-Assisted Navigation**
- 🌙 **Automatic Nighttime Lighting**
- 🆘 **Emergency Button + SMS + Location Sharing**
- 💧 **Water Detection**

---

## 🚧 Potential Future Features
- 🔋 **Battery Low Alert** 
- 🚑 **Fall Detection** 
- 📏 **Obstacle Height Detection**

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
