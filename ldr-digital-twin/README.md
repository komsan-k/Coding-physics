
# LDR Digital Twin with VPython
**ESP32 + LDR + MQTT + VPython Visualization Lab**

---

## Lab Title
Cyber‑Physical Visualization of Light Intensity Using an LDR Sensor and VPython

---

## Learning Objectives

After completing this lab, students will be able to:

- Understand the concept of a Cyber‑Physical System (CPS)
- Interface an LDR sensor with an ESP32
- Publish sensor data using MQTT
- Subscribe to MQTT data using Python
- Visualize real‑time sensor values using VPython
- Map physical measurements to a 3D digital twin representation

---

## CPS Architecture

Physical World → Sensor → ESP32 → MQTT Broker → Python → VPython Visualization

| CPS Layer | Implementation |
|----------|----------------|
| Physical | Light intensity |
| Sensor | LDR |
| Edge Device | ESP32 |
| Communication | MQTT |
| Cyber Layer | Python |
| Visualization | VPython 3D scene |

---

## Hardware Requirements

- ESP32 development board
- LDR (Light Dependent Resistor)
- 10kΩ resistor
- Breadboard
- Jumper wires
- Computer with Python installed

---

## Circuit Diagram

Voltage divider configuration:

3.3V  
 │  
[LDR]  
 │  
 ├──→ GPIO34 (ADC)  
 │  
[10kΩ]  
 │  
GND  

---

## Install Python Libraries

```bash
pip install vpython
pip install paho-mqtt
```

---

## ESP32 Arduino Code

```cpp
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_WIFI";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

const int LDR_PIN = 34;

void setup_wifi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_LDR")) {
    } else {
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  int ldrValue = analogRead(LDR_PIN);

  char msg[10];
  sprintf(msg,"%d",ldrValue);

  client.publish("esp32/ldr", msg);

  delay(200);
}
```

---

## VPython Visualization Code

```python
from vpython import *
import paho.mqtt.client as mqtt

scene = canvas(title="LDR Digital Twin")

ball = sphere(
    pos=vector(0,0,0),
    radius=0.5,
    color=color.white
)

latest_value = 0

def on_connect(client, userdata, flags, rc):
    client.subscribe("esp32/ldr")

def on_message(client, userdata, msg):
    global latest_value
    latest_value = int(msg.payload.decode())

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("broker.hivemq.com",1883,60)
client.loop_start()

while True:

    rate(30)

    norm = latest_value / 4095

    ball.radius = 0.2 + norm
    ball.color = vector(norm, norm, 0.2)
```

---

## Experiment Procedure

1. Assemble the LDR circuit on the breadboard.
2. Upload the ESP32 program using Arduino IDE.
3. Confirm LDR readings in the Serial Monitor.
4. Install Python libraries.
5. Run the VPython Python script.
6. Cover the LDR with your hand.
7. Shine a light on the LDR.
8. Observe the sphere changing size and brightness.

---

## Expected Results

| Light Condition | LDR Value | Sphere |
|-----------------|-----------|--------| Dark | Low | Small sphere |
| Medium light | Medium | Medium sphere |
| Bright light | High | Large bright sphere |

---

## Extension Activities

Possible extensions:

- Add Node‑RED dashboard visualization
- Add data logging to CSV
- Use multiple sensors (temperature, motion)
- Implement automatic LED lighting control
- Build a full Smart Lighting CPS system

---

## Learning Outcome

This experiment demonstrates a simple **physical‑to‑digital mapping** where real‑world sensor data is transformed into a real‑time 3D digital twin using VPython and MQTT.

Students gain experience with:

- Embedded sensing
- IoT communication
- Python visualization
- Cyber‑Physical Systems architecture

---
