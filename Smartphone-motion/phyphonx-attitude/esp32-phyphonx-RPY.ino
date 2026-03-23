#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// -------- WiFi --------
const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";

// -------- phyphox API --------
const char* url = "http://172.19.177.163:8080/get?yaw&pitch&roll";

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Connect WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {

    HTTPClient http;
    http.begin(url);

    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();

      // Parse JSON
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);

      if (!error) {
        float roll  = doc["buffer"]["roll"]["buffer"][0];
        float pitch = doc["buffer"]["pitch"]["buffer"][0];
        float yaw   = doc["buffer"]["yaw"]["buffer"][0];

        Serial.println("===== RPY =====");
        Serial.print("Roll  : "); Serial.println(roll);
        Serial.print("Pitch : "); Serial.println(pitch);
        Serial.print("Yaw   : "); Serial.println(yaw);
        Serial.println("================\n");

      } else {
        Serial.println("JSON parse error!");
      }

    } else {
      Serial.print("HTTP error: ");
      Serial.println(httpCode);
    }

    http.end();

  } else {
    Serial.println("WiFi disconnected!");
  }

  delay(500); // 0.5 sec update
}
