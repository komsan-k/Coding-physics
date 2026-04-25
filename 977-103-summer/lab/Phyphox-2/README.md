# Lab 2: 2-D Motion Physics Engine using Phyphox

## 1. Objective
- Extend 1-D motion to 2-D motion
- Use accelerometer data (ax, ay)
- Compute velocity and position vectors
- Visualize trajectory

## 2. Theory

a = (ax, ay)  
v = (vx, vy)  
r = (x, y)  

Discrete:
vx = vx + ax * dt  
vy = vy + ay * dt  
x = x + vx * dt  
y = y + vy * dt  

Speed:
v = sqrt(vx^2 + vy^2)

## 3. Setup
1. Open Phyphox
2. Select "Acceleration without g"
3. Enable Remote Access
4. Note IP address

## 4. Python Code

```python
import requests
import time
import matplotlib.pyplot as plt

PHONE_IP = "192.168.1.50"
URL = f"http://{PHONE_IP}:8080/get?accX&accY"

x, y = 0.0, 0.0
vx, vy = 0.0, 0.0

traj_x, traj_y = [], []

last_time = time.time()

while len(traj_x) < 200:
    data = requests.get(URL).json()
    ax = data["buffer"]["accX"]["buffer"][-1]
    ay = data["buffer"]["accY"]["buffer"][-1]

    now = time.time()
    dt = now - last_time
    last_time = now

    if abs(ax) < 0.05: ax = 0
    if abs(ay) < 0.05: ay = 0

    vx = 0.98 * vx + ax * dt
    vy = 0.98 * vy + ay * dt

    x += vx * dt
    y += vy * dt

    traj_x.append(x)
    traj_y.append(y)

    time.sleep(0.05)

plt.plot(traj_x, traj_y)
plt.xlabel("X")
plt.ylabel("Y")
plt.title("2-D Trajectory")
plt.grid()
plt.axis('equal')
plt.show()
```

## 5. Tasks
- Straight motion
- Diagonal motion
- Circular motion
- Random motion

## 6. Analysis
- Plot trajectory
- Compute speed
- Observe drift

## 7. Discussion
- Why drift increases in 2-D?
- How to reduce noise?

## 8. Conclusion
Smartphone + 2D physics engine = CPS digital twin
