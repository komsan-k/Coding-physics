/*
  ESP32 + MPU6050 + MQTT Publisher
  --------------------------------
  Publishes:
    esp32/mpu6050/pitch
    esp32/mpu6050/roll
    esp32/mpu6050/yaw
    esp32/mpu6050/json

  Libraries:
    - WiFi.h
    - PubSubClient by Nick O'Leary
    - Wire.h
    - Adafruit_MPU6050
    - Adafruit_Sensor
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <math.h>

// ---------------- Wi-Fi ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- MQTT ----------------
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* topic_pitch = "esp32/mpu6050/pitch";
const char* topic_roll  = "esp32/mpu6050/roll";
const char* topic_yaw   = "esp32/mpu6050/yaw";
const char* topic_json  = "esp32/mpu6050/json";

// ---------------- Objects ----------------
WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_MPU6050 mpu;

// ---------------- Orientation ----------------
float pitch = 0.0f;   // degrees
float roll  = 0.0f;   // degrees
float yaw   = 0.0f;   // degrees

unsigned long lastMicros = 0;
unsigned long lastPublish = 0;
const unsigned long publishInterval = 100; // ms

const float alpha = 0.98f; // complementary filter

// ---------------- Wi-Fi ----------------
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
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());
}

// ---------------- MQTT ----------------
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT... ");

    String clientId = "ESP32-MPU6050-";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" retrying in 2 seconds");
      delay(2000);
    }
  }
}

// ---------------- MPU6050 ----------------
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

  Serial.println("MPU6050 initialized");
}

// ---------------- Orientation update ----------------
void updateOrientation() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  unsigned long now = micros();
  float dt = (now - lastMicros) / 1000000.0f;
  lastMicros = now;

  if (dt <= 0.0f || dt > 0.1f) {
    dt = 0.01f;
  }

  // Accelerometer-based pitch and roll
  float accPitch = atan2(a.acceleration.y,
                         sqrt(a.acceleration.x * a.acceleration.x +
                              a.acceleration.z * a.acceleration.z)) * 180.0f / PI;

  float accRoll = atan2(-a.acceleration.x, a.acceleration.z) * 180.0f / PI;

  // Gyro in deg/s
  float gyroX = g.gyro.x * 180.0f / PI;
  float gyroY = g.gyro.y * 180.0f / PI;
  float gyroZ = g.gyro.z * 180.0f / PI;

  // Complementary filter
  pitch = alpha * (pitch + gyroX * dt) + (1.0f - alpha) * accPitch;
  roll  = alpha * (roll  + gyroY * dt) + (1.0f - alpha) * accRoll;

  // Gyro-only yaw (drifts over time)
  yaw += gyroZ * dt;

  if (yaw > 180.0f) yaw -= 360.0f;
  if (yaw < -180.0f) yaw += 360.0f;
}

// ---------------- Publish MQTT ----------------
void publishMotion() {
  char bufPitch[16];
  char bufRoll[16];
  char bufYaw[16];
  char jsonPayload[128];

  dtostrf(pitch, 0, 3, bufPitch);
  dtostrf(roll,  0, 3, bufRoll);
  dtostrf(yaw,   0, 3, bufYaw);

  client.publish(topic_pitch, bufPitch);
  client.publish(topic_roll,  bufRoll);
  client.publish(topic_yaw,   bufYaw);

  snprintf(jsonPayload, sizeof(jsonPayload),
           "{\"pitch\":%.3f,\"roll\":%.3f,\"yaw\":%.3f}",
           pitch, roll, yaw);

  client.publish(topic_json, jsonPayload);

  Serial.print("Pitch: ");
  Serial.print(pitch, 2);
  Serial.print("  Roll: ");
  Serial.print(roll, 2);
  Serial.print("  Yaw: ");
  Serial.println(yaw, 2);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Wire.begin(21, 22); // SDA, SCL for ESP32
  initMPU();

  connectWiFi();

  client.setServer(mqtt_server, mqtt_port);

  Serial.println("System ready");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();

  updateOrientation();

  unsigned long now = millis();
  if (now - lastPublish >= publishInterval) {
    lastPublish = now;
    publishMotion();
  }
}
