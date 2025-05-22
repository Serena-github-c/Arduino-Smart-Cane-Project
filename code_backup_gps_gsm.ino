#include <TinyGPS++.h>
const int ldrPin = A0;
const int ledPin = 13;


TinyGPSPlus gps;

const int buttonPin = 7;

const int waterSensorPin = 28;  // PA6 / Analog pin 6  
const int trigPin = 25;     // Ultrasonic Trigger pin
const int echoPin = 27;     // Ultrasonic Echo pin
const int buzzerPin = 26;   // Buzzer control pin    // PA7 / Analog pin 7

void setup() {
    /* Ali
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  */

  /* Serena
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);    // Debug only
  Serial1.begin(9600);   // GPS
  Serial2.begin(9600);   // GSM

  delay(2000);
  sendCommand("AT");
  sendCommand("AT+CMGF=1");
  sendCommand("AT+CSCS=\"GSM\"");
  */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
   pinMode(waterSensorPin, INPUT);   // Read water sensor signal (S pin)
     
  Serial.begin(9600);
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

  /* Serena
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
  */
  int waterState = digitalRead(waterSensorPin);

  if (waterState == HIGH) {  // LOW means water is detected
    Serial.println("⚠️ Water Detected!");
    digitalWrite(buzzerPin, HIGH);  // Turn ON buzzer
  } else {
    Serial.println("✅ No Water");
    digitalWrite(buzzerPin, LOW);   // Turn OFF buzzer
  }

  delay(300); // Wait a bit
   // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo response time
  long duration = pulseIn(echoPin, HIGH);

  // Convert to distance (cm)
  float distance = duration * 0.034 / 2;

  // Print to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Activate buzzer if object is too close
  if (distance > 0 && distance < 15) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }

  delay(300); // Stabilize readings
}
