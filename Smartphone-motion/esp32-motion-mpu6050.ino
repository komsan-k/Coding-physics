/*
  ESP32 + MPU6050 HTTP Motion Server
  ----------------------------------
  Serves pitch, roll, yaw at:

    http://ESP32_IP/get?pitch&roll&yaw

  JSON format is compatible with your Python script:
    data["buffer"]["pitch"]["buffer"][0]
    data["buffer"]["roll"]["buffer"][0]
    data["buffer"]["yaw"]["buffer"][0]

  Libraries:
    - WiFi.h
    - WebServer.h
    - Wire.h
    - Adafruit_MPU6050
    - Adafruit_Sensor

  Install from Library Manager:
    - Adafruit MPU6050
    - Adafruit Unified Sensor
*/

#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// ---------------- Wi-Fi ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- Web server ----------------
WebServer server(80);

// ---------------- MPU6050 ----------------
Adafruit_MPU6050 mpu;

// ---------------- Orientation variables ----------------
float pitch = 0.0f;   // degrees
float roll  = 0.0f;   // degrees
float yaw   = 0.0f;   // degrees

unsigned long lastMicros = 0;

// Complementary filter coefficient
const float alpha = 0.98f;

// ---------------- HTML root page ----------------
void handleRoot() {
  String html = "<html><body>";
  html += "<h2>ESP32 MPU6050 Motion Server</h2>";
  html += "<p>Use endpoint: <a href=\"/get?pitch&roll&yaw\">/get?pitch&roll&yaw</a></p>";
  html += "<p>Pitch: " + String(pitch, 2) + " deg</p>";
  html += "<p>Roll: " + String(roll, 2) + " deg</p>";
  html += "<p>Yaw: " + String(yaw, 2) + " deg</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

// ---------------- JSON endpoint ----------------
void handleGet() {
  String json = "{";
  json += "\"buffer\":{";
  json += "\"pitch\":{\"buffer\":[" + String(pitch, 3) + "]},";
  json += "\"roll\":{\"buffer\":[" + String(roll, 3) + "]},";
  json += "\"yaw\":{\"buffer\":[" + String(yaw, 3) + "]}";
  json += "}";
  json += "}";

  server.send(200, "application/json", json);
}

// ---------------- Wi-Fi connect ----------------
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

// ---------------- MPU init ----------------
void initMPU() {
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found. Check wiring.");
    while (true) {
      delay(1000);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(200);
  lastMicros = micros();
}

// ---------------- Orientation update ----------------
void updateOrientation() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  unsigned long now = micros();
  float dt = (now - lastMicros) / 1000000.0f;
  lastMicros = now;

  if (dt <= 0.0f || dt > 0.1f) dt = 0.01f;

  // Accelerometer angles
  float accPitch = atan2(a.acceleration.y,
                         sqrt(a.acceleration.x * a.acceleration.x +
                              a.acceleration.z * a.acceleration.z)) * 180.0f / PI;

  float accRoll = atan2(-a.acceleration.x, a.acceleration.z) * 180.0f / PI;

  // Gyro is in rad/s from Adafruit library
  float gyroX = g.gyro.x * 180.0f / PI; // deg/s
  float gyroY = g.gyro.y * 180.0f / PI; // deg/s
  float gyroZ = g.gyro.z * 180.0f / PI; // deg/s

  // Complementary filter
  pitch = alpha * (pitch + gyroX * dt) + (1.0f - alpha) * accPitch;
  roll  = alpha * (roll  + gyroY * dt) + (1.0f - alpha) * accRoll;

  // Yaw from gyro only -> will drift over time
  yaw += gyroZ * dt;

  // Keep yaw in [-180, 180]
  if (yaw > 180.0f) yaw -= 360.0f;
  if (yaw < -180.0f) yaw += 360.0f;
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(); // default ESP32 I2C pins: SDA=21, SCL=22

  initMPU();
  connectWiFi();

  server.on("/", handleRoot);
  server.on("/get", handleGet);
  server.begin();

  Serial.println("HTTP server started");
  Serial.println("Open this in browser:");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  updateOrientation();
  server.handleClient();

  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 500) {
    lastPrint = millis();
    Serial.print("Pitch: ");
    Serial.print(pitch, 2);
    Serial.print("  Roll: ");
    Serial.print(roll, 2);
    Serial.print("  Yaw: ");
    Serial.println(yaw, 2);
  }
}
