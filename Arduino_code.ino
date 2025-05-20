const int ldrPin = A0;
const int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);  // علشان نطبع قيمة LDR
}

void loop() {
  int lightVal = analogRead(ldrPin);
  Serial.println(lightVal);  // بتظهر القيمة بالـ Serial Monitor

  if (lightVal < 1500) { // لما يكون في عتمة
    digitalWrite(ledPin, HIGH);  // شغل الـ LED
  } else {
    digitalWrite(ledPin, LOW);   // طفي الـ LED
  }

  delay(200);
}
