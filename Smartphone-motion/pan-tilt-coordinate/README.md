
# RPY to 2‑DOF Pan–Tilt Coordinate System

This document explains how to convert a **Roll–Pitch–Yaw (RPY)** orientation system into a **2‑Degree‑of‑Freedom (2‑DOF) Pan–Tilt coordinate system** suitable for servo‑based platforms such as:

- camera tracking systems
- antenna pointing systems
- robotics platforms
- Cyber‑Physical Systems (CPS) laboratories

---

# 1. Original Orientation System (RPY)

Smartphones and IMU sensors typically provide orientation using **three rotational axes**:

| Axis | Meaning | Rotation |
|-----|--------|---------|
| Roll (R) | rotation around X axis | left–right tilt |
| Pitch (P) | rotation around Y axis | forward–back tilt |
| Yaw (Y) | rotation around Z axis | heading / rotation |

Mathematically:

Orientation = Rz(yaw) · Ry(pitch) · Rx(roll)

This represents a **3‑DOF orientation system**.

---

# 2. Pan–Tilt System (2 DOF)

A **pan‑tilt mechanism** contains only two rotational axes.

| DOF | Motion | Axis |
|----|-------|------|
| Pan | rotate left/right | vertical axis |
| Tilt | rotate up/down | horizontal axis |

Therefore the system is reduced as:

RPY → Pan–Tilt

Mapping:

| RPY | Pan–Tilt |
|----|----------|
| yaw | pan |
| pitch | tilt |
| roll | not used |

Thus:

Pan = yaw  
Tilt = pitch

---

# 3. DOF Representation

The reduced system becomes:

DOF = 2

State vector:

q = [pan, tilt]

Where

pan = θp  
tilt = θt

Rotation matrix:

R = Rz(pan) · Ry(tilt)

---

# 4. Coordinate System

```
        Z
        ↑
        │
        │
        O────→ X
       /
      /
     Y
```

Pan–Tilt motion:

Pan → rotation around Z axis  
Tilt → rotation around Y axis

---

# 5. Servo Mapping

Typical hardware implementation:

| Motion | Servo |
|------|------|
| pan | Servo 1 |
| tilt | Servo 2 |

Typical ranges:

pan : −90° → +90°  
tilt : −45° → +45°

---

# 6. Convert Smartphone RPY → Pan‑Tilt

Example conversion:

```
pan  = yaw
tilt = pitch
```

Example code:

```cpp
float pan  = yaw;
float tilt = pitch;
```

---

# 7. Map Orientation to Servo Angles

Example mapping:

```cpp
int servoPan  = map(pan,  -90, 90, 0, 180);
int servoTilt = map(tilt, -45, 45, 30, 150);
```

Servo commands:

```cpp
servoPan.write(servoPan);
servoTilt.write(servoTilt);
```

---

# 8. Kinematic Model

Rotation matrix representation:

R = Rz(pan) · Ry(tilt)

Expanded form:

```
R =
[ cos(pan)cos(tilt)   -sin(pan)   cos(pan)sin(tilt) ]
[ sin(pan)cos(tilt)    cos(pan)   sin(pan)sin(tilt) ]
[   -sin(tilt)            0           cos(tilt)     ]
```

---

# 9. Control Flow Architecture

```
Smartphone motion
        ↓
Pitch, Roll, Yaw
        ↓
Select 2 DOF
Pan  = Yaw
Tilt = Pitch
        ↓
Servo mapping
        ↓
Pan–Tilt platform
```

---

# 10. Advantages of 2‑DOF Systems

| Feature | Benefit |
|-------|--------|
| simpler mechanics | only two servos |
| easier control | fewer calculations |
| stable | fewer singularities |
| cheaper | less hardware |

---

# 11. Example Applications

2‑DOF Pan–Tilt systems are widely used in:

- camera tracking systems
- robotic vision platforms
- antenna pointing systems
- laser scanning platforms
- Cyber‑Physical Systems laboratories

---

# 12. Suggested Mechanical Platform

```
        Camera / Sensor
             │
        ┌─────────┐
        │  Tilt   │
        │ Servo   │
        └────┬────┘
             │
        ┌─────────┐
        │  Pan    │
        │ Servo   │
        └────┬────┘
             │
            Base
```

---

# Summary

The **RPY orientation model** from smartphone sensors can be simplified to a **2‑DOF Pan‑Tilt model** by selecting:

Pan = Yaw  
Tilt = Pitch

This simplification allows efficient implementation using **two servo motors**, making it ideal for:

- robotics
- IoT platforms
- antenna tracking systems
- Cyber‑Physical Systems laboratories
