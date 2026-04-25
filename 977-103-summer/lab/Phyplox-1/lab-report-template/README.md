# Lab Report Template
## 1-D Motion Physics Engine using Phyphox

---

## Student Information
- Name:
- Student ID:
- Course:
- Instructor:
- Date:

---

## 1. Abstract
(150–250 words summarizing objective, method, results, conclusion)

---

## 2. Objectives
- Implement 1-D motion physics engine
- Acquire acceleration data using Phyphox
- Compute velocity and position
- Analyze noise and drift
- Demonstrate CPS digital twin

---

## 3. Background Theory

### Kinematics
v(t) = v0 + ∫ a(t) dt  
x(t) = x0 + ∫ v(t) dt  

### Discrete Form
v_k = v_{k-1} + a_k * dt  
x_k = x_{k-1} + v_k * dt  

### Dynamics
F = ma  
KE = 1/2 m v^2  

---

## 4. Materials and Tools
- Smartphone
- Phyphox
- Python (requests, numpy)

---

## 5. System Architecture
Phyphox → API → Physics Engine → Motion Estimation → Digital Twin

---

## 6. Methodology
1. Setup Phyphox (Acceleration without g)
2. Enable Remote Access
3. Acquire acceleration data
4. Integrate to velocity and position
5. Analyze drift

---

## 7. Implementation
```python
# Paste your Python code here
```

---

## 8. Results

### Raw Data
| Time | Acceleration | Velocity | Position |
|------|-------------|----------|----------|

### Graphs
- Acceleration vs Time
- Velocity vs Time
- Position vs Time

---

## 9. Discussion
- Noise effects
- Drift issues
- Accuracy
- Improvements

---

## 10. CPS Perspective
Explain physical, cyber, and digital twin layers

---

## 11. Conclusion
Summarize findings and limitations

---

## 12. Appendix
```python
# Full code
```

---

## 13. Evaluation Rubric
| Criteria | Marks |
|---------|------|
| Abstract | 10 |
| Theory | 15 |
| Methodology | 15 |
| Implementation | 20 |
| Results | 15 |
| Discussion | 15 |
| Conclusion | 10 |
