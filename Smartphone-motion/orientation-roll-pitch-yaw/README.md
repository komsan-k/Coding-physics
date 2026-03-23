# MPU6050 Orientation Estimation (Roll, Pitch, Yaw)

---

## 📘 Overview

Converting raw data from an **MPU6050** into stable **Roll, Pitch, and Yaw (RPY)** values is a classic problem in embedded systems and robotics.

The MPU6050 is a **6-axis motion tracking sensor** that includes:

- 3-axis Accelerometer  
- 3-axis Gyroscope  

⚠️ It does **NOT include a magnetometer**, which affects Yaw estimation.

---

## 🔷 1. Roll and Pitch from Accelerometer

The accelerometer measures the **gravity vector**, allowing us to estimate tilt.

### 📐 Equations

Roll = atan2(Ay, sqrt(Ax² + Az²)) × (180/π)  
Pitch = atan2(-Ax, sqrt(Ay² + Az²)) × (180/π)

### ⚠️ Limitation

- Sensitive to vibration  
- Noisy output  

---

## 🔷 2. Gyroscope Integration

The gyroscope measures **angular velocity (°/s)**.

### 📐 Equation

Angle = Angle_prev + (GyroRate × dt)

### ⚠️ Limitation

- Drift over time  
- Accumulates error  

---

## 🔷 3. Sensor Fusion (Complementary Filter)

To combine the strengths of both sensors:

- Accelerometer → long-term stability  
- Gyroscope → short-term responsiveness  

### 📐 Complementary Filter

Angle = 0.98 × (Angle + GyroRate × dt) + 0.02 × AccelAngle

### 🧠 Insight

- High-pass filter → Gyroscope  
- Low-pass filter → Accelerometer  

---

## 🔷 4. Yaw Limitation

### ❗ Key Issue

The MPU6050 **cannot determine absolute Yaw**.

### Why?

- Accelerometer only senses gravity (downward)
- No reference to Earth’s magnetic field (North)

### Result

- Yaw is **relative only**
- Drift increases over time

---

## 🔷 5. Solution for Absolute Yaw

To obtain stable Yaw:

- Use **MPU9250** (with magnetometer)  
- Or add external **HMC5883L**  

---

## 📊 Summary Table

| Metric       | Source         | Strength                  | Weakness              |
|-------------|--------------|--------------------------|-----------------------|
| Roll/Pitch  | Accel + Gyro | Stable with fusion       | Sensitive to vibration |
| Yaw         | Gyro only    | Good short-term tracking | Drifts over time      |

---

## 🚀 Applications

- Robotics orientation  
- Drone stabilization  
- Camera gimbals  
- CPS motion tracking systems  
- Pan–Tilt control platforms  

---

## ✅ Summary

The MPU6050 provides:

- Accurate **Roll and Pitch** using sensor fusion  
- Limited **Yaw** estimation due to lack of magnetometer  

The **Complementary Filter** is a simple and effective method for real-time orientation estimation on microcontrollers.

---

## 🔧 Next Step

You can implement this using:

- Arduino (ESP32 / UNO)  
- Python (for visualization or digital twin)  

👉 Ask for code if needed (Arduino / Python / Node-RED integration)
