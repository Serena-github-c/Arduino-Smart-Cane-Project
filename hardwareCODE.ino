#include <DFRobotDFPlayerMini.h>

// Pin assignments
const int trigFront = 28, echoFront = 29;
const int trigLeft  = 30, echoLeft  = 31;
const int trigRight = 32, echoRight = 33;
const int ldrPin = A0;      // LDR sensor pin
const int ledPin = 22;      // LED pin

// Detection parameters
const int FRONT_THRESHOLD = 40;  // cm - obstacle detection distance
const int SIDE_THRESHOLD = 30;   // cm - side clearance needed for navigation
const int MIN_DISTANCE = 2;      // cm - minimum valid reading
const int MAX_DISTANCE = 400;    // cm - maximum valid reading

// Light detection parameters
const int LIGHT_THRESHOLD = 300; // LDR threshold (0-1023) - adjust as needed
const unsigned long LIGHT_CHECK_INTERVAL = 500; // Check light every 500ms

// Timing parameters
const unsigned long MESSAGE_DELAY = 3000;    // 3s between same messages
const unsigned long SENSOR_DELAY = 50;      // 50ms between sensor readings
const unsigned long DEBOUNCE_TIME = 200;    // 200ms debounce for state changes

// Audio setup
DFRobotDFPlayerMini mp3;

// State management
int lastState = 0;              // 0=clear, 1=go_right, 2=go_left
unsigned long lastPlayTime = 0;
unsigned long lastSensorTime = 0;
unsigned long stateChangeTime = 0;
unsigned long lastLightCheck = 0;  // Last time we checked light level

// Distance filtering (simple moving average)
const int FILTER_SIZE = 3;
float frontReadings[FILTER_SIZE] = {0};
float leftReadings[FILTER_SIZE] = {0};
float rightReadings[FILTER_SIZE] = {0};
int filterIndex = 0;

void setup() {
  Serial.begin(9600);  // For debugging
  Serial1.begin(9600); // For MP3 player
  
  // Initialize MP3 player
  if (!mp3.begin(Serial1)) {
    Serial.println("MP3 player initialization failed!");
  }
  
  delay(500);  // Wait for MP3 player to initialize
  mp3.volume(25);  // Slightly lower volume for better clarity
  
  // Configure sensor pins
  pinMode(trigFront, OUTPUT);  pinMode(echoFront, INPUT);
  pinMode(trigLeft, OUTPUT);   pinMode(echoLeft, INPUT);
  pinMode(trigRight, OUTPUT);  pinMode(echoRight, INPUT);
  pinMode(ledPin, OUTPUT);     // Configure LED pin as output
  pinMode(ldrPin, INPUT);      // Configure LDR pin as input (though analog pins are input by default)
  
  // Initialize filter arrays
  for (int i = 0; i < FILTER_SIZE; i++) {
    frontReadings[i] = MAX_DISTANCE;
    leftReadings[i] = MAX_DISTANCE;
    rightReadings[i] = MAX_DISTANCE;
  }
  
  Serial.println("Blind Navigation System with Auto-Light Initialized");
}

// Enhanced distance measurement with error handling
float measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Longer timeout for better reliability
  long duration = pulseIn(echoPin, HIGH, 35000); // 35ms timeout
  
  if (duration == 0) {
    return MAX_DISTANCE;  // No echo received
  }
  
  float distance = (duration * 0.034) / 2.0;
  
  // Validate reading
  if (distance < MIN_DISTANCE || distance > MAX_DISTANCE) {
    return MAX_DISTANCE;  // Invalid reading
  }
  
  return distance;
}

// Apply simple moving average filter
float filterDistance(float newReading, float* readings) {
  readings[filterIndex] = newReading;
  
  float sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += readings[i];
  }
  
  return sum / FILTER_SIZE;
}

// Determine navigation state based on sensor readings
int determineNavigationState(float frontDist, float leftDist, float rightDist) {
  // No front obstacle - clear path
  if (frontDist >= FRONT_THRESHOLD) {
    return 0;  // Clear
  }
  
  // Front obstacle detected - check sides
  bool leftBlocked = (leftDist < SIDE_THRESHOLD);
  bool rightBlocked = (rightDist < SIDE_THRESHOLD);
  
  Serial.print("Front: "); Serial.print(frontDist);
  Serial.print(" Left: "); Serial.print(leftDist);
  Serial.print(" Right: "); Serial.println(rightDist);
  
  // Decision logic
  if (leftBlocked && rightBlocked) {
    // All three sensors detect obstacles - critical situation
    Serial.println("Critical: All directions blocked!");
    return 3;  // All blocked - play warning sound
  } else if (leftBlocked && !rightBlocked) {
    Serial.println("Decision: Go Right");
    return 1;  // Go right (left is blocked)
  } else if (rightBlocked && !leftBlocked) {
    Serial.println("Decision: Go Left");
    return 2;  // Go left (right is blocked)
  } else {
    // Both sides clear - choose based on which side has more space
    if (leftDist > rightDist) {
      Serial.println("Decision: Go Left (more space)");
      return 2;  // Go left (more space)
    } else {
      Serial.println("Decision: Go Right (more space)");
      return 1;  // Go right (more space)
    }
  }
}

// Check light level and control LED
void checkLightLevel() {
  int lightLevel = analogRead(ldrPin);  // Read LDR value (0-1023)
  
  // Debug output (remove in final version if needed)
  Serial.print("Light Level: ");
  Serial.println(lightLevel);
  
  // Control LED based on light level
  if (lightLevel < LIGHT_THRESHOLD) {
    digitalWrite(ledPin, HIGH);  // Turn LED ON in dark conditions
    Serial.println("LED: ON (Dark detected)");
  } else {
    digitalWrite(ledPin, LOW);   // Turn LED OFF in bright conditions  
    Serial.println("LED: OFF (Light detected)");
  }
}

void loop() {
  unsigned long currentTime = millis();
  
  // Rate limiting for sensor readings
  if (currentTime - lastSensorTime < SENSOR_DELAY) {
    return;
  }
  lastSensorTime = currentTime;
  
  // Read all sensors
  float frontRaw = measureDistance(trigFront, echoFront);
  float leftRaw = measureDistance(trigLeft, echoLeft);
  float rightRaw = measureDistance(trigRight, echoRight);
  
  // Apply filtering
  float frontFiltered = filterDistance(frontRaw, frontReadings);
  float leftFiltered = filterDistance(leftRaw, leftReadings);
  float rightFiltered = filterDistance(rightRaw, rightReadings);
  
  // Update filter index
  filterIndex = (filterIndex + 1) % FILTER_SIZE;
  
  // Determine current state
  int currentState = determineNavigationState(frontFiltered, leftFiltered, rightFiltered);
  
  // State change logic with debouncing
  if (currentState != lastState) {
    if (currentTime - stateChangeTime > DEBOUNCE_TIME) {
      stateChangeTime = currentTime;
      
      // Play appropriate message
      if (currentState == 1 && (currentTime - lastPlayTime > MESSAGE_DELAY)) {
        mp3.play(2);  // 002.mp3 → "Go right"
        Serial.println("Playing: Go Right");
        lastPlayTime = currentTime;
      } else if (currentState == 2 && (currentTime - lastPlayTime > MESSAGE_DELAY)) {
        mp3.play(1);  // 001.mp3 → "Go left"
        Serial.println("Playing: Go Left");
        lastPlayTime = currentTime;
      } else if (currentState == 3 && (currentTime - lastPlayTime > MESSAGE_DELAY)) {
        mp3.play(3);  // 003.mp3 → Warning for all sides blocked
        Serial.println("Playing: All directions blocked warning");
        lastPlayTime = currentTime;
      }
      
      lastState = currentState;
    }
  } else if (currentState != 0 && currentState == lastState) {
    // Same non-clear state - repeat message after delay
    if (currentTime - lastPlayTime > MESSAGE_DELAY) {
      if (currentState == 1) {
        mp3.play(2);  // Repeat "Go right"
        Serial.println("Repeating: Go Right");
      } else if (currentState == 2) {
        mp3.play(1);  // Repeat "Go left"
        Serial.println("Repeating: Go Left");
      } else if (currentState == 3) {
        mp3.play(3);  // Repeat warning for all sides blocked
        Serial.println("Repeating: All directions blocked warning");
      }
      lastPlayTime = currentTime;
    }
  }
  
  // Reset state when path is clear
  if (currentState == 0) {
    lastState = 0;
  }
  
  // Check light level periodically
  if (currentTime - lastLightCheck >= LIGHT_CHECK_INTERVAL) {
    checkLightLevel();
    lastLightCheck = currentTime;
  }
}