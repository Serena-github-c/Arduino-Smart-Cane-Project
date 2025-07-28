# Multifunctional Smart Cane for the Visually Impaired

This project is a smart assistive device designed to enhance mobility and safety for visually impaired individuals. Built using an **Arduino Mega 2560**, it integrates multiple sensors and modules to detect obstacles, provide environmental feedback, and send emergency alerts.

## Features

- **Obstacle Detection**: Uses three ultrasonic sensors (front, left, right) with audio feedback to guide direction.
- **Light-Based LED Activation**: An LDR sensor automatically turns on an LED when ambient light is low.
- **Water Hazard Detection**: A water sensor alerts the user to puddles or wet surfaces using an audio warning.
- **GPS Tracking**: Continuously tracks location coordinates via a GPS module.
- **Emergency Alert System**: Sends GPS location via email to a predefined emergency contact when a button is pressed.
- **Audio Feedback**: Uses DFPlayer Mini to play voice commands like "go left", "go right", or "water detected".

## Components Used

- Arduino Mega 2560
- HC-SR04 Ultrasonic Sensors (×3)
- LDR + LED
- HW-038 Water Sensor
- DFPlayer Mini + Speaker
- GPS Module (NEO-6M)
- ESP32 with Wi-Fi (to send the emergency SMS)
- Pushbuttons, battery, resistors, and supporting hardware

## How It Works

1. **Sensors scan the environment** for obstacles and hazards.
2. **Voice commands guide the user** based on sensor input.
3. **In low light**, the LED automatically turns on for visibility.
4. **In emergencies**, the user can press a button to send their location via SMS.
5. **Real-time location data** is printed to the serial monitor for logging and debugging.

## Project Structure

- `hardware code/` – Arduino source code + ESP32 emergency button code
- `Proteus Simulation/` – Schema + code
- `media/` – Images, schematic photos, demo videos

## Demo

![Smart Cane Diagram](media/cane -front view.png)  
*Image: Front view of prototype*
![Cane Side view](<media/cane - side view.jpeg>)

> Consult the /media folder for demo videos

## Future Improvements

- Add vibration motor for silent alerts
- Improve power efficiency for longer battery life
- Integrate voice-to-text commands
- Compact PCB layout for wearable design

## License

This project is for academic purposes under the [MIT License](LICENSE).

---

## Contributors

This project was collaboratively developed by:

- [@Ali-ghassan-yazbeck](https://github.com/Ali-ghassan-yazbeck)
- [@Serena-github-c](https://github.com/Serena-github-c)     
- [@zeinattar](https://github.com/zeinattar)

All three contributors are engineering students who worked together on system design, code development, hardware integration, and documentation.
