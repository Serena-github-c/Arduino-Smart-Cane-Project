# Arduino-Smart-Cane-Project
Smart Cane for Visually Impaired: An Arduino-based assistive device that uses ultrasonic sensors to detect nearby obstacles and water puddles. It provides real-time feedback through vibrations and a buzzer. The system can also use a speaker to read alerts aloud and integrates GPS for location tracking and navigation assistance.

# Components

.ESP32-CAM: the project requires object detection using AI, voice feedback, and wireless communication — features that aren't practical or even possible with the Arduino Uno or Mega alone.

.Ultrasonic sensor module | HC-SR04(5pieces): measures the distance to objects in front of the user and alerts them if something is too close

.DFPlayer Mini MP3 Module: Plays pre-recorded MP3 files (e.g., object names)

.MicroSD Card (with adapter): Stores the MP3 audio files used by DFPlayer

.Mini Speaker (3W 4ohm):  Outputs the sound from the DFPlayer so the user can hear it

.YL-83 or FC-37 Water sensor: Detects water or puddles to alert the user of slippery areas

.SIM800L GSM Module: Sends an SMS with GPS coordinates when a button is pressed

.NEO-6M GPS Module: Gets the real-time location to include in the SMS

.Push Button: User can press it to send location in emergencies

.LDR: Detects low light conditions (dark environments)

.White LED:  Lights up the cane when it’s dark so the user is visible

.18650 Li-ion Battery: Portable and high capacity battery for the whole system

.TP4056 Charging Module (with Protection): Safely charges the 18650 battery via USB and protects it

.USB to TTL Adapter: Uploads code to ESP32-CAM and powers it during development

.jumper wires female-to-female male-to-male female-to-male: for wirings


