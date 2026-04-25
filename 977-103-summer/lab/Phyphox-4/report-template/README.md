# Lab Report Template
## Lab 4: 3D Rigid-Body Physics Engine using Phyphox

---

## Student Information
- Name:
- Student ID:
- Course:
- Instructor:
- Date:

---

## 1. Abstract
(150–250 words summarizing objective, methodology, results, and conclusion)

---

## 2. Objectives
- Implement a 3D rigid-body physics engine  
- Fuse accelerometer and gyroscope data  
- Estimate position, velocity, and orientation  
- Analyze drift, noise, and sensor fusion performance  
- Demonstrate CPS digital twin  

---

## 3. Background Theory

### 3.1 3D Kinematics
a = (ax, ay, az)  
v = ∫ a dt  
r = ∫ v dt  

### 3.2 Angular Motion
ω = (ωx, ωy, ωz)  

### 3.3 Orientation (Euler Angles)
- Roll (φ)  
- Pitch (θ)  
- Yaw (ψ)  

### 3.4 Sensor Fusion
θ = α(θ + ω·dt) + (1-α)θ_acc  

---

## 4. Materials and Tools
- Smartphone  
- Phyphox  
- Python (requests, numpy, matplotlib)  

---

## 5. System Architecture
Phyphox → API → Sensor Fusion → 3D Physics Engine → Digital Twin  

Explain system:

---

## 6. Methodology
1. Acquire accelerometer and gyroscope data  
2. Integrate gyro for orientation  
3. Correct using accelerometer  
4. Compute velocity and position  
5. Analyze results  

---

## 7. Implementation

```python
# Insert your Python code here
```

Explain your implementation:

---

## 8. Results

### 8.1 Raw Data
| Time | ax | ay | az | roll | pitch | yaw |
|------|----|----|----|------|-------|-----|

### 8.2 Graphs
- Roll vs Time  
- Pitch vs Time  
- Yaw vs Time  
- Position (x, y, z)  

---

## 9. Discussion
- Drift in 3D position  
- Gyroscope bias  
- Sensor fusion effectiveness  
- Limitations and improvements  

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
# Paste full code here
```

---

## 13. Optional Extension
- Kalman filter  
- Madgwick filter  
- Node-RED 3D visualization  
- TinyML motion classification  

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
