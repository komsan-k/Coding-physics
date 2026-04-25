# Lab 3: Rotational Motion Physics Engine using Phyphox

## Abstract
This lab presents a rotational motion physics engine using smartphone gyroscope data from Phyphox. Angular velocity is integrated to estimate angular displacement, while angular acceleration, torque, and rotational energy are computed. The system demonstrates a CPS-based digital twin for rotational dynamics.

---

## 1. Introduction
Modern Cyber-Physical Systems (CPS) leverage embedded sensors for real-time physical modeling. Smartphones provide accessible IMU sensors (accelerometer + gyroscope), enabling software-defined physics engines. This lab focuses on rotational motion modeling using gyroscope data.

---

## 2. Theory

### Angular Velocity
ω = dθ/dt  

### Angular Displacement
θ = ∫ ω dt  

### Angular Acceleration
α = dω/dt  

### Torque
τ = Iα  

### Rotational Energy
KE = 1/2 I ω²  

---

## 3. Methodology

1. Acquire gyroscope data (ωx, ωy, ωz) from Phyphox  
2. Perform numerical integration to compute θ  
3. Estimate angular acceleration  
4. Compute torque and energy  
5. Visualize results  

---

## 4. Implementation

```python
import requests
import time
import numpy as np

PHONE_IP = "192.168.1.50"
URL = f"http://{PHONE_IP}:8080/get?gyrZ"

theta = 0.0
prev_w = 0.0
I = 0.002

last_time = time.time()

while True:
    data = requests.get(URL).json()
    wz = data["buffer"]["gyrZ"]["buffer"][-1]

    now = time.time()
    dt = now - last_time
    last_time = now

    if abs(wz) < 0.01:
        wz = 0

    theta += wz * dt
    alpha = (wz - prev_w) / dt
    torque = I * alpha
    ke = 0.5 * I * wz**2

    prev_w = wz

    print(f"θ={theta:.3f}, ω={wz:.3f}, α={alpha:.3f}, τ={torque:.5f}, KE={ke:.5f}")

    time.sleep(0.05)
```

---

## 5. Results
Students should plot:
- Angular displacement vs time  
- Angular velocity vs time  

---

## 6. Discussion
- Sensor noise introduces drift  
- Integration accumulates error  
- Damping or filtering improves stability  

---

## 7. CPS Perspective
- Physical: smartphone rotation  
- Cyber: physics engine  
- Digital Twin: computed angular state  

---

## 8. Conclusion
This lab demonstrates a rotational physics engine using smartphone sensors. It highlights the feasibility of CPS-based digital twins using low-cost hardware.

---

## Keywords
CPS, Digital Twin, Gyroscope, Rotational Motion, Phyphox
