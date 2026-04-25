# Lab: 1-D Motion Physics Engine using Phyphox

## 1. Objective
- Implement a software-defined physics engine for 1-D motion
- Use smartphone sensors (Phyphox) as real-time data sources
- Compute velocity, position, force, and energy

## 2. Learning Outcomes
- Understand 1-D kinematics and dynamics
- Acquire real-time sensor data using Phyphox
- Implement numerical integration

## 3. Theory
v(t) = v0 + ∫ a(t) dt  
x(t) = x0 + ∫ v(t) dt  

Discrete:
v_k = v_{k-1} + a_k * dt  
x_k = x_{k-1} + v_k * dt  

## 4. Setup
1. Install Phyphox
2. Open "Acceleration without g"
3. Enable Remote Access
4. Note IP address

## 5. Python Code

```python
import requests
import time

PHONE_IP = "192.168.1.50"
URL = f"http://{PHONE_IP}:8080/get?accX"

mass = 0.2
x, v = 0.0, 0.0
last_time = time.time()

while True:
    data = requests.get(URL).json()
    ax = data["buffer"]["accX"]["buffer"][-1]

    now = time.time()
    dt = now - last_time
    last_time = now

    if abs(ax) < 0.05:
        ax = 0.0

    v = 0.98 * v + ax * dt
    x = x + v * dt

    print(f"a={ax:.3f}, v={v:.3f}, x={x:.3f}")
    time.sleep(0.1)
```

## 6. Tasks
- Constant velocity test
- Acceleration/deceleration
- Drift observation

## 7. Discussion
- Why does drift occur?
- How does noise affect results?

## 8. Conclusion
Smartphone + physics engine = CPS digital twin
