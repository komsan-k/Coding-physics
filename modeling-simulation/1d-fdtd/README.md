# 1D FDTD Electromagnetic Simulator (Python)

---

## 📘 Overview

This project provides a **simple Python-based electromagnetic (EM) simulator** using the **1D Finite-Difference Time-Domain (FDTD)** method.

It solves Maxwell’s curl equations for:

- **Ez** → Electric field  
- **Hy** → Magnetic field  

This is an excellent starting point for learning EM simulation before moving to 2D/3D solvers.

---

## ⚙️ Features

- Gaussian pulse source  
- Free-space propagation  
- Dielectric slab interaction  
- Reflection and transmission visualization  
- Animation support  

---

## 🧠 What the Simulator Demonstrates

- Incident wave propagation  
- Reflection from dielectric material  
- Transmission through media  
- Effect of permittivity  

---

## 📐 Mathematical Model

Maxwell’s curl equations in 1D:

```
∂Ez/∂t = (1/ε) ∂Hy/∂x
∂Hy/∂t = (1/μ) ∂Ez/∂x
```

The FDTD method discretizes these equations in space and time using the **Yee grid**.

---

## 🧪 Python Implementation

```python
Here is a simple Python-based EM simulator using the 1D FDTD method to simulate electromagnetic wave propagation.

It solves the 1D Maxwell curl equations for:

Ez → electric field
Hy → magnetic field

This is a good starting point for learning EM simulation before moving to 2D/3D solvers.

1D FDTD EM Simulator in Python
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# ============================================================
# 1D FDTD Electromagnetic Wave Simulation
# Solves Maxwell's equations in 1D using Yee's algorithm
# Fields:
#   Ez -> Electric field
#   Hy -> Magnetic field
# ============================================================

# Physical constants
c0 = 3e8                     # Speed of light in vacuum (m/s)
mu0 = 4e-7 * np.pi           # Permeability of free space
eps0 = 1 / (mu0 * c0**2)     # Permittivity of free space

# Simulation parameters
Nx = 400                     # Number of spatial cells
dx = 1e-3                    # Spatial step (1 mm)
dt = dx / (2 * c0)           # Time step (must satisfy CFL condition)
Nt = 700                     # Number of time steps

# Material properties
eps_r = np.ones(Nx)          # Relative permittivity
mu_r = np.ones(Nx)           # Relative permeability

# Example dielectric slab
eps_r[200:260] = 4.0         # Higher permittivity region

# Field arrays
Ez = np.zeros(Nx)
Hy = np.zeros(Nx)

# For simple absorbing boundary condition
Ez_old_left = 0.0
Ez_old_right = 0.0

# Source parameters (Gaussian pulse)
source_position = 100
t0 = 40
spread = 12

# Storage for visualization
Ez_history = []

# ============================================================
# FDTD Time-Stepping Loop
# ============================================================
for n in range(Nt):
    # Update magnetic field Hy
    for i in range(Nx - 1):
        Hy[i] = Hy[i] + (dt / (mu0 * mu_r[i] * dx)) * (Ez[i + 1] - Ez[i])

    # Update electric field Ez
    for i in range(1, Nx):
        Ez[i] = Ez[i] + (dt / (eps0 * eps_r[i] * dx)) * (Hy[i] - Hy[i - 1])

    # Gaussian source injection
    pulse = np.exp(-0.5 * ((n - t0) / spread) ** 2)
    Ez[source_position] += pulse

    # Simple absorbing boundary condition
    Ez[0] = Ez_old_left
    Ez_old_left = Ez[1]

    Ez[-1] = Ez_old_right
    Ez_old_right = Ez[-2]

    # Store history every few steps
    if n % 4 == 0:
        Ez_history.append(Ez.copy())

# ============================================================
# Visualization: Static snapshots
# ============================================================
x = np.arange(Nx) * dx * 1000  # Convert to mm

plt.figure(figsize=(10, 5))
plt.plot(x, Ez_history[10], label="Step 10")
plt.plot(x, Ez_history[50], label="Step 50")
plt.plot(x, Ez_history[-1], label="Final Step")
plt.axvspan(200 * dx * 1000, 260 * dx * 1000, alpha=0.2, label="Dielectric slab")
plt.xlabel("Position (mm)")
plt.ylabel("Electric Field Ez")
plt.title("1D FDTD Electromagnetic Wave Propagation")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.show()

# ============================================================
# Optional animation
# ============================================================
fig, ax = plt.subplots(figsize=(10, 5))
line, = ax.plot(x, Ez_history[0], lw=2)
ax.axvspan(200 * dx * 1000, 260 * dx * 1000, alpha=0.2)
ax.set_xlim(x[0], x[-1])
ax.set_ylim(-1.2, 1.2)
ax.set_xlabel("Position (mm)")
ax.set_ylabel("Electric Field Ez")
ax.set_title("1D FDTD Animation")
ax.grid(True)

def update(frame):
    line.set_ydata(Ez_history[frame])
    ax.set_title(f"1D FDTD Animation - Frame {frame}")
    return line,

ani = FuncAnimation(fig, update, frames=len(Ez_history), interval=40, blit=True)
plt.tight_layout()
plt.show()
What this simulator does

This code simulates:

a Gaussian EM pulse
traveling through free space
hitting a dielectric slab
then producing reflection and transmission

So you can directly observe:

incident wave
reflected wave
transmitted wave
effect of material permittivity
Main idea behind the equations

In 1D, Maxwell’s curl equations become:

∂
𝐸
𝑧
∂
𝑡
=
1
𝜖
∂
𝐻
𝑦
∂
𝑥
∂t
∂E
z
	​

	​

=
ϵ
1
	​

∂x
∂H
y
	​

	​

∂
𝐻
𝑦
∂
𝑡
=
1
𝜇
∂
𝐸
𝑧
∂
𝑥
∂t
∂H
y
	​

	​

=
μ
1
	​

∂x
∂E
z
	​

	​


The FDTD method discretizes both space and time and updates fields alternately using the Yee scheme.

Important parts of the code
1. Spatial grid
Nx = 400
dx = 1e-3

This creates 400 cells with 1 mm spacing.

2. Time step
dt = dx / (2 * c0)

This satisfies the CFL stability condition.

3. Dielectric region
eps_r[200:260] = 4.0

This creates a material with relative permittivity 4.

4. Source
pulse = np.exp(-0.5 * ((n - t0) / spread) ** 2)
Ez[source_position] += pulse

This injects a Gaussian pulse.

5. Absorbing boundaries

The simple boundary condition reduces reflections from the edges.

What you can modify

You can easily extend this code.

Change the material
eps_r[200:260] = 2.5
Make two dielectric slabs
eps_r[150:200] = 3.0
eps_r[250:320] = 6.0
Use a sinusoidal source

Replace the Gaussian pulse with:

freq = 2e9
pulse = np.sin(2 * np.pi * freq * n * dt)
Ez[source_position] += pulse
Add conductivity loss

You can include lossy media by modifying the Ez update equation.

What this is useful for

This simple simulator helps you understand:

wave propagation
reflection and transmission
dielectric loading
numerical EM fundamentals
how FDTD works before moving to 2D/3D antenna problems

It is especially useful before building:

2D TE/TM FDTD solvers
metasurface simulations
antenna aperture models
EM digital twin environments
```

---

## 🧭 Simulation Workflow

1. Initialize grid and fields  
2. Define material properties  
3. Inject EM source  
4. Update Hy field  
5. Update Ez field  
6. Apply boundary conditions  
7. Store results  
8. Visualize output  

---

## 🔧 Key Parameters

| Parameter | Description |
|----------|-------------|
| Nx | Number of spatial cells |
| dx | Spatial step size |
| dt | Time step (CFL condition) |
| Nt | Number of time steps |

---

## 🧱 Material Modeling

Example dielectric region:

```python
eps_r[200:260] = 4.0
```

This creates a slab with higher permittivity.

---

## ⚡ Source Example

Gaussian pulse:

```python
pulse = np.exp(-0.5 * ((n - t0) / spread) ** 2)
Ez[source_position] += pulse
```

---

## 🧪 What You Can Modify

- Change dielectric properties  
- Add multiple materials  
- Use sinusoidal sources  
- Add conductivity (lossy media)  
- Extend to 2D/3D FDTD  

---

## 📊 Outputs

- Electric field distribution (Ez)  
- Time evolution of wave  
- Reflection and transmission behavior  

---

## 🎥 Visualization

- Static plots  
- Animated wave propagation  

---

## 🚀 Applications

- EM education  
- Wave propagation analysis  
- Antenna fundamentals  
- Metasurface pre-modeling  
- CPS EM digital twin development  

---

## ⚠️ Limitations

- 1D only  
- Simple absorbing boundary  
- No full-wave 3D effects  

---

## ✅ Summary

This simulator provides a **fundamental understanding of EM wave behavior and FDTD methods**, forming the basis for advanced EM simulation and CPS-integrated digital twin systems.
