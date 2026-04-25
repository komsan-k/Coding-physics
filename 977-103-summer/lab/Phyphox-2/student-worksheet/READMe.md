# Student Worksheet 
## Lab 2: 2-D Motion Physics Engine using Phyphox

---

## Student Information
Name: __________________________  
Student ID: _____________________  
Date: __________________________  

---

## Part A: Concept Understanding

Q1. Write the vector form of acceleration.  
Answer: ______________________________

Q2. Write the discrete-time equations for vx and vy.  
Answer: ______________________________

Q3. How do you compute speed from vx and vy?  
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

| Time | ax | ay | vx | vy | x | y |
|------|----|----|----|----|---|---|
| 1 | | | | | | |
| 2 | | | | | | |
| 3 | | | | | | |
| 4 | | | | | | |
| 5 | | | | | | |

---

## Part D: Experiment

Q4. What happens when moving only in X direction?  
____________________________________  

Q5. Describe trajectory for diagonal motion  
____________________________________  

Q6. What happens in circular motion?  
____________________________________  

---

## Part E: Analysis

Q7. Why is drift worse in 2-D?  
____________________________________  

Q8. How can orientation affect results?  
____________________________________  

---

## Part F: Extension

Define motion states based on speed:

STOP: __________________  
SLOW: __________________  
FAST: __________________  

---

## Part G: Reflection

How does this represent a 2-D CPS Digital Twin?  
____________________________________  

---

# Instructor Solution

Q1: a = (ax, ay)  

Q2:  
vx = vx + ax * dt  
vy = vy + ay * dt  

Q3:  
v = sqrt(vx^2 + vy^2)  

Q4: Straight line along X-axis  

Q5: Diagonal straight line  

Q6: Distorted loop due to drift  

Q7: Double integration in two axes accumulates more error  

Q8: Misalignment causes incorrect axis measurement  

Example classification:  
STOP < 0.05  
SLOW < 0.5  
FAST ≥ 0.5  
