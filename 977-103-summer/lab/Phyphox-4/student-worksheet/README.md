# Student Worksheet + Instructor Solution
## Lab 4: 3D Rigid-Body Physics Engine using Phyphox

---

## Student Information
Name: __________________________  
Student ID: _____________________  
Date: __________________________  

---

## Part A: Concept Understanding

Q1. Write the 3D acceleration vector.  
Answer: ______________________________  

Q2. Write the equation for velocity from acceleration.  
Answer: ______________________________  

Q3. What are the three Euler angles?  
Answer: ______________________________  

---

## Part B: Setup Checklist

| Task | ✓/✗ |
|------|----|
| Installed Phyphox | |
| Enabled Remote Access | |
| Same Wi-Fi | |
| Got IP Address | |

Phone IP: ______________________  

---

## Part C: Data Collection

| Time | ax | ay | az | roll | pitch | yaw |
|------|----|----|----|------|-------|-----|
| 1 | | | | | | |
| 2 | | | | | | |
| 3 | | | | | | |
| 4 | | | | | | |
| 5 | | | | | | |

---

## Part D: Experiment

Q4. What happens when the phone is static?  
____________________________________  

Q5. What happens when tilting forward/backward?  
____________________________________  

Q6. What happens during rotation around Z-axis?  
____________________________________  

---

## Part E: Analysis

Q7. Why is position drift severe in 3D?  
____________________________________  

Q8. Why do we need sensor fusion?  
____________________________________  

---

## Part F: Extension

Define motion states:

STATIC: __________________  
MOTION: __________________  
AGGRESSIVE: __________________  

---

## Part G: Reflection

How does this represent a 3D CPS Digital Twin?  
____________________________________  
<!--
---

# Instructor Solution

Q1: a = (ax, ay, az)  

Q2: v = ∫ a dt  

Q3: Roll, Pitch, Yaw  

Q4: Minimal movement, stable orientation  

Q5: Pitch changes significantly  

Q6: Yaw changes, rotation observed  

Q7: Double integration accumulates large errors  

Q8: To combine stability (acc) and responsiveness (gyro)  

Example classification:  
STATIC < 0.1  
MOTION < 2  
AGGRESSIVE ≥ 2  
-->
