#include <WiFi.h>
#include <PubSubClient.h>

// -------------------------
// Wi-Fi settings
// -------------------------
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// -------------------------
// MQTT settings
// -------------------------
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_topic = "esp32/ldr";

// -------------------------
// LDR pin
// -------------------------
const int LDR_PIN = 34;   // ADC input

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastPublish = 0;
const unsigned long publishInterval = 500; // ms

// -------------------------
// Connect to Wi-Fi
// -------------------------
void setupWiFi() {
  Serial.println();
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

// -------------------------
// Reconnect to MQTT
// -------------------------
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT... ");

    String clientId = "ESP32-LDR-";
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

void setup() {
  Serial.begin(115200);
  delay(1000);

  // ESP32 ADC setup
  analogReadResolution(12); // 0 to 4095

  setupWiFi();

  client.setServer(mqtt_server, mqtt_port);

  Serial.println("System ready");
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    setupWiFi();
  }

  if (!client.connected()) {
    reconnectMQTT();
  }

  client.loop();

  unsigned long now = millis();
  if (now - lastPublish >= publishInterval) {
    lastPublish = now;

    int ldrValue = analogRead(LDR_PIN);

    char payload[16];
    snprintf(payload, sizeof(payload), "%d", ldrValue);

    bool ok = client.publish(mqtt_topic, payload);

    Serial.print("LDR ADC = ");
    Serial.print(ldrValue);
    Serial.print("  | Publish: ");
    Serial.println(ok ? "OK" : "FAILED");
  }
}
