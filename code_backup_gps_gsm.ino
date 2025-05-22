#include <TinyGPS++.h>
const int ldrPin = A0;
const int ledPin = 13;


TinyGPSPlus gps;

const int buttonPin = 7;

void setup() {
    /* Ali
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  */

  pinMode(buttonPin, INPUT);
  Serial.begin(9600);    // Debug only
  Serial1.begin(9600);   // GPS
  Serial2.begin(9600);   // GSM

  delay(2000);
  sendCommand("AT");
  sendCommand("AT+CMGF=1");
  sendCommand("AT+CSCS=\"GSM\"");
}

void loop() {
    /* Ali
  int lightVal = analogRead(ldrPin);
  Serial.println(lightVal);  // بتظهر القيمة بالـ Serial Monitor

  if (lightVal < 1500) { // لما يكون في عتمة
    digitalWrite(ledPin, HIGH);  
  } else {
    digitalWrite(ledPin, LOW);   
  }

  delay(200);
  */
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }

  if (digitalRead(buttonPin) == HIGH) {
    sendEmergencySMS();
    delay(5000);  // Prevent multiple triggers
  }

  delay(100);
}

void sendCommand(String cmd) {
  Serial2.println(cmd);
  delay(500);
}

void sendEmergencySMS() {
  if (gps.location.isValid()) {
    String msg = "EMERGENCY:\nLat: " + String(gps.location.lat(), 6) + 
                 "\nLng: " + String(gps.location.lng(), 6);

    Serial2.println("AT+CMGF=1");
    delay(500);
    Serial2.println("AT+CMGS=\"+96171594791\"");  
    delay(500);
    Serial2.print(msg);
    delay(500);
    Serial2.write(26); // End SMS (CTRL+Z)
    delay(3000);
  } else {
    Serial.println("GPS not ready");
  }
}
