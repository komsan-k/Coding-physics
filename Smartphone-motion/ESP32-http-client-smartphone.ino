/*
  ESP32 HTTP Client for Smartphone Motion Data
  --------------------------------------------
  Reads smartphone motion data from:

    http://192.168.1.8:8080/get?pitch&roll&yaw

  Expected JSON format:

  {
    "buffer": {
      "pitch": {"buffer":[... ]},
      "roll":  {"buffer":[... ]},
      "yaw":   {"buffer":[... ]}
    }
  }

  Required libraries:
    - WiFi.h
    - HTTPClient.h
    - ArduinoJson
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// ---------------- Wi-Fi ----------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// ---------------- Smartphone motion URL ----------------
const char* motionURL = "http://192.168.1.8:8080/get?pitch&roll&yaw";

// ---------------- Timing ----------------
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

  Serial.println("ESP32 Smartphone Motion HTTP Client Ready");
}

void loop() {
  unsigned long now = millis();

  if (now - lastRead >= readInterval) {
    lastRead = now;
    readSmartphoneMotion();
  }
}
