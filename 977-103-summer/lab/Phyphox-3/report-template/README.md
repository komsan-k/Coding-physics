# Lab Report Template
## Rotational Motion Physics Engine using Phyphox

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
- Implement a rotational motion physics engine
- Acquire gyroscope data (ωx, ωy, ωz)
- Compute angular displacement and acceleration
- Analyze drift and noise
- Demonstrate CPS digital twin

---

## 3. Background Theory

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

## 4. Materials and Tools
- Smartphone
- Phyphox
- Python (requests, numpy, matplotlib)

---

## 5. System Architecture
Phyphox → API → Rotational Physics Engine → Angular State → Digital Twin

Explain the system:

---

## 6. Methodology
1. Open Phyphox (Gyroscope)
2. Enable Remote Access
3. Acquire ω data
4. Integrate to θ
5. Compute α, τ, KE
6. Plot results

---

## 7. Implementation

```python
# Insert your Python code here
```

Explanation:

---

## 8. Results

### 8.1 Raw Data
| Time | ω (rad/s) | θ (rad) | α (rad/s²) |
|------|-----------|---------|------------|

### 8.2 Graphs
- Angular velocity vs time
- Angular displacement vs time

---

## 9. Discussion
- Drift in angular displacement
- Noise effects
- Sensor limitations
- Improvement methods

---

## 10. CPS Perspective
Explain:
- Physical system
- Cyber model
- Digital twin representation

---

## 11. Conclusion
Summarize findings and limitations

---

## 12. Appendix

### A. Full Code
```python
# Paste full code
```

---

## 13. Optional Extension
- Filtering (low-pass / Kalman)
- Rotation classification
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
