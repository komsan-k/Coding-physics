# Student Worksheet
## Lab: 1-D Motion Physics Engine using Phyphox

---

## Student Information
Name: __________________________  
Student ID: _____________________  
Date: __________________________  

---

## Part A: Concept Understanding

Q1. Write the equation for velocity from acceleration.  
Answer:  
____________________________________  

Q2. Write the discrete-time equation for position.  
Answer:  
____________________________________  

Q3. What is the unit of acceleration?  
Answer:  
____________________________________  

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

| Time | Acceleration | Velocity | Position |
|------|-------------|----------|----------|
| 1 | | | |
| 2 | | | |
| 3 | | | |
| 4 | | | |
| 5 | | | |

---

## Part D: Experiment

Q6. What happens to position when still?  
____________________________________  

Q7. Describe velocity behavior during motion  
____________________________________  

Q8. What happens to acceleration during sudden stop?  
____________________________________  

---

## Part E: Analysis

Q9. Why does drift occur?  
____________________________________  

Q10. How to reduce noise?  
____________________________________  

---

## Part F: Extension

Define your motion classes:

STOP: __________________  
SLOW: __________________  
FAST: __________________  

---

## Part G: Reflection

How does this relate to CPS Digital Twin?  
____________________________________  

<!--
---

# Instructor Solution

Q1: v = v0 + ∫a dt  
Q2: x_k = x_{k-1} + v_k dt  
Q3: m/s²  

Drift: noise + integration error  
Noise reduction: filtering, damping, Kalman  

Example classification:
STOP < 0.05  
SLOW < 0.5  
FAST ≥ 0.5  
-->
