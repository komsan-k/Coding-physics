# Lab Report Template
## 2-D Motion Physics Engine using Phyphox

---

## Student Information
- Name:
- Student ID:
- Course:
- Instructor:
- Date:

---

## 1. Abstract
(150–250 words: objective, method, results, conclusion)

---

## 2. Objectives
- Extend 1-D motion to 2-D motion
- Acquire acceleration data (ax, ay)
- Compute velocity and position vectors
- Analyze drift and noise
- Demonstrate CPS digital twin

---

## 3. Background Theory

### 3.1 Vector Motion
a = (ax, ay)  
v = (vx, vy)  
r = (x, y)  

### 3.2 Discrete Equations
vx = vx + ax * dt  
vy = vy + ay * dt  
x = x + vx * dt  
y = y + vy * dt  

### 3.3 Speed
v = sqrt(vx^2 + vy^2)

### 3.4 Energy
KE = 1/2 m v^2  

---

## 4. Materials and Tools
- Smartphone
- Phyphox
- Python (requests, numpy, matplotlib)

---

## 5. System Architecture
Phyphox → API → 2D Physics Engine → Trajectory → Digital Twin

Explain the system:

---

## 6. Methodology
1. Open Phyphox (Acceleration without g)
2. Enable Remote Access
3. Acquire ax, ay data
4. Integrate to vx, vy
5. Integrate to x, y
6. Plot trajectory

---

## 7. Implementation

```python
# Insert your Python code here
```

Explanation:

---

## 8. Results

### 8.1 Raw Data
| Time | ax | ay | vx | vy | x | y |
|------|----|----|----|----|---|---|

### 8.2 Graphs
- X vs Time
- Y vs Time
- Trajectory (X vs Y)

---

## 9. Discussion
- Drift behavior in 2D
- Noise effects
- Axis misalignment
- Accuracy limitations
- Improvements

---

## 10. CPS Perspective
Explain:
- Physical system
- Cyber model
- Digital twin representation

---

## 11. Conclusion
Summarize findings, challenges, and improvements

---

## 12. Appendix

### A. Full Code
```python
# Paste full code
```

---

## 13. Optional Extension
- Filtering (low-pass / Kalman)
- Motion classification
- Node-RED dashboard

---

## 14. Evaluation Rubric
| Criteria | Marks |
|---------|------|
| Abstract | 10 |
| Theory | 15 |
| Methodology | 15 |
| Implementation | 20 |
| Results | 15 |
| Discussion | 15 |
| Conclusion | 10 |
