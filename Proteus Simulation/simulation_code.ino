
#include <TinyGPS++.h>
TinyGPSPlus gps;
const int ldrPin = A0;
const int ledPin = 30;
const int buttonPin = 7;
const int waterSensorPin = 28;  // PA6 / Analog pin 6  
const int trigPin = 25;     // Ultrasonic Trigger pin
const int echoPin = 27;     // Ultrasonic Echo pin
const int buzzerPin = 26;   // Buzzer control pin    // PA7 / Analog pin 7

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(waterSensorPin, INPUT);   // Read water sensor signal (S pin)

  Serial.begin(9600);    
  Serial1.begin(9600);   // GPS
  Serial2.begin(9600);   // GSM

  delay(1000);
  sendCommand("AT");
  sendCommand("AT+CMGF=1");
  sendCommand("AT+CSCS=\"GSM\"");
  
}

void loop() {
  
  // Light LDR Sensor Detection
  int lightVal = analogRead(ldrPin);
  Serial.println(lightVal);  

  digitalWrite(ledPin, lightVal<1500 ? HIGH : LOW);
  delay(200);
  

  // GPS
  while (Serial1.available()) {
    gps.encode(Serial1.read());
  }



  // Emergency Button
  static bool smsSent = false;
  if (digitalRead(buttonPin) == HIGH  && !smsSent) {
    sendEmergencySMS();
    smsSent = true;
  }
  else if (digitalRead(buttonPin) == LOW){
    smsSent = false;
  }

  
  // water detection
  int waterState = digitalRead(waterSensorPin);
  //Serial.println(waterState == LOW ? " Water Detected!" : " No Water");  

  // ultrasonic sensor (object detection)
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo response time
  long duration = pulseIn(echoPin, HIGH, 30000);  //timeout after 30000 microseconds = 30 milliseconds
  // Convert to distance (cm)
  float distance = duration * 0.034 / 2;

  // Print to Serial Monitor
  //Serial.print("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  // Activate buzzer
  // 2 components activate the buzzer so we need to prioritize alerts in logic

    if (distance < 15) {
    digitalWrite(buzzerPin, HIGH);
  } else if (waterState == HIGH) {
    digitalWrite(buzzerPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);
  }
  
  delay(100);

}



// functions used for GPS
void sendCommand(String cmd) {
  Serial2.println(cmd);
  delay(400);
}

void sendEmergencySMS() {
  Serial2.println("Button pressed — attempting to send SMS");

    Serial2.println("Valid GPS — sending SMS");

    String msg = "EMERGENCY:\nLat: " + String(gps.location.lat(), 6) + 
                 "\nLng: " + String(gps.location.lng(), 6);

    Serial2.println("AT+CMGF=1");
    delay(200);
    Serial2.println("AT+CMGS=\"+96171555888\"");  
    delay(200);
    Serial2.print(msg);
    delay(200);
    Serial2.write(26); // End SMS (CTRL+Z)
    delay(2000);

  
  
}


