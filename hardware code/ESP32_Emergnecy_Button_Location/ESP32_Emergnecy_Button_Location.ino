#include <WiFi.h>
#include <ESP_Mail_Client.h>

// WiFi credentials
const char* ssid = "";
const char* password = "";

// SMTP server settings
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

// Email account credentials
#define AUTHOR_EMAIL ""         // your Gmail address
#define AUTHOR_PASSWORD ""      // your Gmail app password

// Recipient email
#define RECIPIENT_EMAIL ""     // email you want to send to

// Define button pin
const int buttonPin = 4;   // GPIO2 (D2)

SMTPSession smtp;
SMTP_Message message;

void setup() {
  Serial.begin(115200);

  // Configure button pin
  pinMode(buttonPin, INPUT_PULLUP);  // Use internal pull-up

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void loop() {
  // Check if button is pressed (LOW because of pull-up)
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button pressed! Sending email...");

    // Configure SMTP session
    ESP_Mail_Session session;
    session.server.host_name = SMTP_HOST;
    session.server.port = SMTP_PORT;
    session.login.email = AUTHOR_EMAIL;
    session.login.password = AUTHOR_PASSWORD;
    session.login.user_domain = "";

    // Compose email
    message.sender.name = "ESP32 Device";
    message.sender.email = AUTHOR_EMAIL;
    message.subject = "⚠️EMERGENCY ALERT: Location of Visually Impaired User";
    message.addRecipient("Recipient", RECIPIENT_EMAIL);

    // Example message content
    String location = "Latitude: 34.01436\nLongitude: 36.18034";
    message.text.content =  "This is an emergency alert from the cane user.\n\nThe user has pressed the emergency button.\n\nLocation:\n" + location + "\n\nRegards";

    // Send email
    if (!smtp.connect(&session)) {
      Serial.println("Could not connect to SMTP server");
    } else if (!MailClient.sendMail(&smtp, &message)) {
      Serial.println("Error sending Email: " + smtp.errorReason());
    } else {
      Serial.println("Email sent successfully!");
    }

    delay(5000); // Wait to avoid multiple emails if button stays pressed
  }

  delay(100); // Small delay to avoid bouncing
}