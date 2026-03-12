/*
  ESP32 + Smartphone Motion HTTP + Smooth Servo Control
  -----------------------------------------------------
  Reads smartphone motion data from:
    http://192.168.1.8:8080/get?pitch&roll&yaw

  Smooth mapping:
    pitch -> servoPitch
    roll  -> servoRoll

  Required libraries:
    - WiFi.h
    - HTTPClient.h
    - ArduinoJson
    - ESP32Servo

  Install from Arduino Library Manager:
    - ArduinoJson
    - ESP32Servo
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP32Servo.h>

// ---------------- Wi-Fi settings ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- Smartphone motion URL ----------------
const char* motionURL = "http://192.168.1.8:8080/get?pitch&roll&yaw";

// ---------------- Servo objects ----------------
Servo servoPitch;
Servo servoRoll;

// ---------------- Servo pins ----------------
const int SERVO_PITCH_PIN = 18;
const int SERVO_ROLL_PIN  = 19;

// ---------------- Timing ----------------
unsigned long lastRead = 0;
const unsigned long readInterval = 100;   // ms

// ---------------- Smoothing ----------------
float filteredPitch = 0.0;
float filteredRoll  = 0.0;
const float smoothAlpha = 0.2;   // 0..1, higher = faster response

// ---------------- Servo limits ----------------
const int SERVO_MIN_ANGLE = 45;
const int SERVO_MAX_ANGLE = 135;

// ---------------- Motion range ----------------
// Expected phone motion range in degrees
const float MOTION_MIN = -45.0;
const float MOTION_MAX =  45.0;

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

float lowPassFilter(float oldValue, float newValue, float alpha) {
  return oldValue + alpha * (newValue - oldValue);
}

int mapFloatToServo(float x, float in_min, float in_max, int out_min, int out_max) {
  float ratio = (x - in_min) / (in_max - in_min);
  float value = out_min + ratio * (out_max - out_min);
  return (int)value;
}

void actFromMotion(float pitch, float roll) {
  // Apply low-pass filtering for smoother movement
  filteredPitch = lowPassFilter(filteredPitch, pitch, smoothAlpha);
  filteredRoll  = lowPassFilter(filteredRoll, roll, smoothAlpha);

  // Map filtered pitch and roll to servo angles
  int pitchServoAngle = mapFloatToServo(filteredPitch, MOTION_MIN, MOTION_MAX,
                                        SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

  int rollServoAngle  = mapFloatToServo(filteredRoll, MOTION_MIN, MOTION_MAX,
                                        SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

  // Keep angles in safe range
  pitchServoAngle = constrain(pitchServoAngle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
  rollServoAngle  = constrain(rollServoAngle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);

  // Write to servos
  servoPitch.write(pitchServoAngle);
  servoRoll.write(rollServoAngle);

  // Print servo outputs
  Serial.print("Filtered Pitch = ");
  Serial.print(filteredPitch, 2);
  Serial.print(" deg, Filtered Roll = ");
  Serial.print(filteredRoll, 2);
  Serial.print(" deg");

  Serial.print(" | ServoPitch = ");
  Serial.print(pitchServoAngle);
  Serial.print(" deg, ServoRoll = ");
  Serial.println(rollServoAngle);
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

      Serial.print("Pitch = ");
      Serial.print(pitch, 2);
      Serial.print(" deg, Roll = ");
      Serial.print(roll, 2);
      Serial.print(" deg, Yaw = ");
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

  // Servo setup
  servoPitch.setPeriodHertz(50);
  servoRoll.setPeriodHertz(50);

  servoPitch.attach(SERVO_PITCH_PIN, 500, 2400);
  servoRoll.attach(SERVO_ROLL_PIN, 500, 2400);

  // Center servos at start
  servoPitch.write(90);
  servoRoll.write(90);

  Serial.println("ESP32 Smartphone Motion Smooth Servo Control Ready");
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= readInterval) {
    lastRead = now;
    readSmartphoneMotion();
  }
}
