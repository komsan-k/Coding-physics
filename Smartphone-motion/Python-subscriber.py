from vpython import box, vector, rate, canvas, color, label
import paho.mqtt.client as mqtt
import math
import json

scene = canvas(title="Smartphone Motion Lab (MQTT)",
               width=900, height=600,
               background=color.white)

phone = box(size=vector(4, 0.3, 2), color=color.blue)

info = label(pos=vector(0, 3, 0),
             text="Waiting for data...",
             box=False)

latest = {"pitch": 0.0, "roll": 0.0, "yaw": 0.0}

def on_connect(client, userdata, flags, reason_code, properties=None):
    client.subscribe("esp32/mpu6050/json")

def on_message(client, userdata, msg):
    global latest
    try:
        latest = json.loads(msg.payload.decode())
    except:
        pass

client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message
client.connect("broker.hivemq.com", 1883, 60)
client.loop_start()

while True:
    rate(30)

    pitch_deg = latest["pitch"]
    roll_deg = latest["roll"]
    yaw_deg = latest["yaw"]

    pitch = math.radians(pitch_deg)
    roll = math.radians(roll_deg)
    yaw = math.radians(yaw_deg)

    axis_x = math.cos(yaw) * math.cos(pitch)
    axis_y = math.sin(pitch)
    axis_z = math.sin(yaw) * math.cos(pitch)

    up_x = -math.sin(roll)
    up_y = math.cos(roll)
    up_z = 0

    phone.axis = vector(axis_x, axis_y, axis_z)
    phone.up = vector(up_x, up_y, up_z)

    info.text = f"Pitch:{pitch_deg:.2f}° Roll:{roll_deg:.2f}° Yaw:{yaw_deg:.2f}°"
