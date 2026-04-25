# Lab 4: 3D Rigid-Body Physics Engine using Phyphox (Accelerometer + Gyroscope Fusion)

## Abstract
This lab presents a 3D rigid-body physics engine using smartphone inertial sensors acquired via Phyphox. Accelerometer and gyroscope data are fused using a complementary filter to estimate orientation (roll, pitch, yaw) and translational motion (position and velocity). The system demonstrates a Cyber-Physical System (CPS) digital twin capable of real-time motion estimation. Experimental results highlight the challenges of drift, noise, and sensor bias in low-cost IMU systems.

---

## 1. Introduction
Modern Cyber-Physical Systems (CPS) rely on real-time sensing, computation, and control. Smartphones provide an accessible platform equipped with inertial measurement units (IMUs), including accelerometers and gyroscopes. This lab extends previous 1D and 2D motion models to full 3D rigid-body dynamics using sensor fusion techniques.

---

## 2. Theory

### 2.1 3D Kinematics
a = (ax, ay, az)  
v = ∫ a dt  
r = ∫ v dt  

### 2.2 Angular Motion
ω = (ωx, ωy, ωz)  

### 2.3 Orientation (Euler Angles)
- Roll (φ)
- Pitch (θ)
- Yaw (ψ)

### 2.4 Complementary Filter
θ = α(θ + ω·dt) + (1-α)θ_acc  

---

## 3. Methodology

1. Acquire accelerometer and gyroscope data from Phyphox  
2. Estimate orientation using gyroscope integration  
3. Correct drift using accelerometer-based angles  
4. Compute velocity and position via integration  
5. Analyze motion behavior  

---

## 4. Implementation

```python
import requests
import time
import numpy as np

PHONE_IP = "192.168.1.50"
URL = f"http://{PHONE_IP}:8080/get?accX&accY&accZ&gyrX&gyrY&gyrZ"

x=y=z=0.0
vx=vy=vz=0.0
roll=pitch=yaw=0.0
alpha=0.98

last_time=time.time()

while True:
    data=requests.get(URL).json()

    ax=data["buffer"]["accX"]["buffer"][-1]
    ay=data["buffer"]["accY"]["buffer"][-1]
    az=data["buffer"]["accZ"]["buffer"][-1]

    wx=data["buffer"]["gyrX"]["buffer"][-1]
    wy=data["buffer"]["gyrY"]["buffer"][-1]
    wz=data["buffer"]["gyrZ"]["buffer"][-1]

    now=time.time()
    dt=now-last_time
    last_time=now

    roll+=wx*dt
    pitch+=wy*dt
    yaw+=wz*dt

    roll_acc=np.arctan2(ay,az)
    pitch_acc=np.arctan2(-ax,np.sqrt(ay**2+az**2))

    roll=alpha*roll+(1-alpha)*roll_acc
    pitch=alpha*pitch+(1-alpha)*pitch_acc

    vx+=ax*dt
    vy+=ay*dt
    vz+=az*dt

    x+=vx*dt
    y+=vy*dt
    z+=vz*dt

    print(f"Pos=({x:.2f},{y:.2f},{z:.2f}) | RPY=({roll:.2f},{pitch:.2f},{yaw:.2f})")

    time.sleep(0.05)
```

---

## 5. Results
Students should plot:
- Roll, pitch, yaw vs time  
- Position (x, y, z)  

---

## 6. Discussion
- Drift accumulates due to integration  
- Gyroscope bias affects orientation  
- Accelerometer provides stability but noisy  

---

## 7. CPS Perspective
- Physical: smartphone motion  
- Cyber: physics + fusion engine  
- Digital Twin: estimated 3D state  

---

## 8. Conclusion
This lab demonstrates a 3D physics engine using low-cost sensors. Sensor fusion improves orientation estimation but position drift remains a challenge.

---

## Keywords
CPS, IMU, Sensor Fusion, Digital Twin, Phyphox, Rigid Body Motion
