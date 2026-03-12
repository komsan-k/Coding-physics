/*
  ESP32 + Smartphone Motion HTTP + 2 Servos
  -----------------------------------------
  Reads smartphone motion data from:
    http://192.168.1.8:8080/get?pitch&roll&yaw

  Servo mapping:
    - Pitch servo: forward/backward
    - Roll servo : left/right

  Required libraries:
    - WiFi.h
    - HTTPClient.h
    - ArduinoJson
    - ESP32Servo
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

// ---------------- Wi-Fi ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- Smartphone URL ----------------
const char* motionURL = "http://192.168.1.8:8080/get?pitch&roll&yaw";

// ---------------- Servos ----------------
Servo servoPitch;
Servo servoRoll;

const int SERVO_PITCH_PIN = 18;
const int SERVO_ROLL_PIN  = 19;

// Center positions
const int CENTER_ANGLE = 90;

// Motion angles
const int FORWARD_ANGLE  = 120;
const int BACKWARD_ANGLE = 60;
const int LEFT_ANGLE     = 60;
const int RIGHT_ANGLE    = 120;

// Thresholds in degrees
const float PITCH_THRESHOLD = 15.0;
const float ROLL_THRESHOLD  = 15.0;

// Timing
unsigned long lastRead = 0;
const unsigned long readInterval = 200; // ms

void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("ESP32 IP address: ");
  Serial.println(WiFi.localIP());
}

void centerServos() {
  servoPitch.write(CENTER_ANGLE);
  servoRoll.write(CENTER_ANGLE);
}

void actFromMotion(float pitch, float roll) {
  int pitchServoAngle = CENTER_ANGLE;
  int rollServoAngle  = CENTER_ANGLE;

  // Forward / backward from pitch
  if (pitch > PITCH_THRESHOLD) {
    pitchServoAngle = FORWARD_ANGLE;
    Serial.println("Action: Tilt Forward");
  } 
  else if (pitch < -PITCH_THRESHOLD) {
    pitchServoAngle = BACKWARD_ANGLE;
    Serial.println("Action: Tilt Backward");
  }

  // Left / right from roll
  if (roll > ROLL_THRESHOLD) {
    rollServoAngle = RIGHT_ANGLE;
    Serial.println("Action: Tilt Right");
  } 
  else if (roll < -ROLL_THRESHOLD) {
    rollServoAngle = LEFT_ANGLE;
    Serial.println("Action: Tilt Left");
  }

  servoPitch.write(pitchServoAngle);
  servoRoll.write(rollServoAngle);
}

void readSmartphoneMotion() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    connectWiFi();
    return;
  }

  HTTPClient http;
  http.begin(motionURL);
  http.setTimeout(1000);

  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();

      StaticJsonDocument<512> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (error) {
        Serial.print("JSON parse failed: ");
        Serial.println(error.c_str());
        http.end();
        return;
      }

      float pitch = doc["buffer"]["pitch"]["buffer"][0] | 0.0;
      float roll  = doc["buffer"]["roll"]["buffer"][0]  | 0.0;
      float yaw   = doc["buffer"]["yaw"]["buffer"][0]   | 0.0;

      Serial.print("Pitch: ");
      Serial.print(pitch, 2);
      Serial.print(" deg, Roll: ");
      Serial.print(roll, 2);
      Serial.print(" deg, Yaw: ");
      Serial.print(yaw, 2);
      Serial.println(" deg");

      actFromMotion(pitch, roll);

    } else {
      Serial.print("HTTP error code: ");
      Serial.println(httpCode);
    }
  } else {
    Serial.print("HTTP GET failed: ");
    Serial.println(http.errorToString(httpCode));
  }

  http.end();
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWiFi();

  // Allow full servo pulse range
  servoPitch.setPeriodHertz(50);
  servoRoll.setPeriodHertz(50);

  servoPitch.attach(SERVO_PITCH_PIN, 500, 2400);
  servoRoll.attach(SERVO_ROLL_PIN, 500, 2400);

  centerServos();

  Serial.println("ESP32 Smartphone Motion Servo Control Ready");
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= readInterval) {
    lastRead = now;
    readSmartphoneMotion();
  }
}
