# 2D FDTD Electromagnetic Simulator (TEz Mode)

---

## 📘 Overview

This project provides a **2D Python-based EM simulator** using the **Finite-Difference Time-Domain (FDTD)** method in **TEz mode**.

It simulates:

- Ez (electric field, out-of-plane)
- Hx, Hy (magnetic field components)
- 2D wave propagation
- Gaussian source excitation
- Interaction with dielectric materials

---

## ⚙️ Features

- 2D grid-based EM simulation
- Gaussian pulse source
- Dielectric block modeling
- Real-time visualization (heatmap)
- Animation of wave propagation

---

## 📐 Maxwell Equations (TEz Mode)

```
Hx = Hx - (dt/μ) * dEz/dy
Hy = Hy + (dt/μ) * dEz/dx
Ez = Ez + (dt/ε) * (dHy/dx - dHx/dy)
```

---

## 🧪 Python Implementation

```python
Great — here is a 2D Python-based EM simulator using a simple FDTD TEz formulation.

This version simulates:

Ez : out-of-plane electric field
Hx, Hy : magnetic field components
2D wave propagation on an 
𝑥
x-
𝑦
y grid
a Gaussian source
a dielectric block
field visualization as a heatmap
2D FDTD EM Simulator in Python
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# ==========================================================
# 2D FDTD Electromagnetic Simulator (TEz mode)
# Fields:
#   Ez(x,y,t)  -> electric field
#   Hx(x,y,t)  -> magnetic field
#   Hy(x,y,t)  -> magnetic field
#
# Maxwell equations used:
#   Hx^{n+1/2} = Hx^{n-1/2} - (dt/mu) * dEz/dy
#   Hy^{n+1/2} = Hy^{n-1/2} + (dt/mu) * dEz/dx
#   Ez^{n+1}   = Ez^n + (dt/eps) * (dHy/dx - dHx/dy)
# ==========================================================

# ---------------------------
# Physical constants
# ---------------------------
c0 = 3e8
mu0 = 4e-7 * np.pi
eps0 = 1 / (mu0 * c0**2)

# ---------------------------
# Grid parameters
# ---------------------------
Nx, Ny = 120, 120          # grid size
dx = 1e-3                  # 1 mm
dy = 1e-3                  # 1 mm

# CFL stability condition for 2D FDTD
dt = 0.99 / (c0 * np.sqrt((1/dx**2) + (1/dy**2)))

Nt = 300                   # number of time steps

# ---------------------------
# Material parameters
# ---------------------------
eps_r = np.ones((Nx, Ny))
mu_r = np.ones((Nx, Ny))

# Example dielectric block in center
eps_r[50:80, 50:80] = 4.0

# ---------------------------
# Field arrays
# ---------------------------
Ez = np.zeros((Nx, Ny))
Hx = np.zeros((Nx, Ny))
Hy = np.zeros((Nx, Ny))

# ---------------------------
# Source parameters
# ---------------------------
src_x, src_y = 30, 60
t0 = 40
spread = 12

# ---------------------------
# Storage for visualization
# ---------------------------
frames = []

# ==========================================================
# Time stepping
# ==========================================================
for n in range(Nt):
    # Update Hx
    Hx[:, :-1] = Hx[:, :-1] - (dt / (mu0 * mu_r[:, :-1] * dy)) * (Ez[:, 1:] - Ez[:, :-1])

    # Update Hy
    Hy[:-1, :] = Hy[:-1, :] + (dt / (mu0 * mu_r[:-1, :] * dx)) * (Ez[1:, :] - Ez[:-1, :])

    # Update Ez (interior only)
    curl_h = ((Hy[1:, 1:-1] - Hy[:-1, 1:-1]) / dx -
              (Hx[1:-1, 1:] - Hx[1:-1, :-1]) / dy)

    Ez[1:-1, 1:-1] = Ez[1:-1, 1:-1] + (dt / (eps0 * eps_r[1:-1, 1:-1])) * curl_h

    # Gaussian pulse source
    pulse = np.exp(-0.5 * ((n - t0) / spread) ** 2)
    Ez[src_x, src_y] += pulse

    # Simple absorbing-like boundary (very basic damping)
    Ez[0, :] *= 0.0
    Ez[-1, :] *= 0.0
    Ez[:, 0] *= 0.0
    Ez[:, -1] *= 0.0

    # Save every few steps
    if n % 3 == 0:
        frames.append(Ez.copy())

# ==========================================================
# Static snapshot
# ==========================================================
plt.figure(figsize=(7, 6))
plt.imshow(frames[-1].T, origin='lower', cmap='RdBu', extent=[0, Nx*dx*1000, 0, Ny*dy*1000])
plt.colorbar(label='Ez Field')
plt.xlabel('x (mm)')
plt.ylabel('y (mm)')
plt.title('2D FDTD EM Simulation (Final Ez Field)')
plt.tight_layout()
plt.show()

# ==========================================================
# Animation
# ==========================================================
fig, ax = plt.subplots(figsize=(7, 6))
im = ax.imshow(frames[0].T, origin='lower', cmap='RdBu',
               extent=[0, Nx*dx*1000, 0, Ny*dy*1000],
               vmin=-1.0, vmax=1.0)

ax.set_xlabel('x (mm)')
ax.set_ylabel('y (mm)')
ax.set_title('2D FDTD EM Wave Propagation')
plt.colorbar(im, ax=ax, label='Ez Field')

def update(frame):
    im.set_array(frames[frame].T)
    ax.set_title(f'2D FDTD EM Wave Propagation - Frame {frame}')
    return [im]

ani = FuncAnimation(fig, update, frames=len(frames), interval=50, blit=True)
plt.tight_layout()
plt.show()
```

## What this code does

This simulator creates a 2D computational region and solves the EM field evolution over time.

Behavior
A Gaussian pulse is launched from one point
The wave spreads in 2D
It reaches the dielectric block
Reflection, slowing, and transmission occur
The Ez field is displayed as a color map
Physical meaning

This is a TEz mode simulation, where:

𝐸
𝑧
≠
0
E
z
	​


=0
𝐻
𝑥
≠
0
H
x
	​


=0
𝐻
𝑦
≠
0
H
y
	​


=0

This is a common 2D simplification for learning computational electromagnetics.

The update equations are derived from Maxwell’s curl equations.

## Key parts you can modify
1. Grid size
Nx, Ny = 120, 120

Larger grid gives a bigger simulation region, but uses more memory and time.

2. Dielectric object
eps_r[50:80, 50:80] = 4.0

This defines a square dielectric block.

You can change it to:

eps_r[40:90, 55:65] = 6.0

for a rectangular slab.

3. Source location
src_x, src_y = 30, 60
4. Source waveform

Currently it is a Gaussian pulse.
You can replace it with a sinusoid:

freq = 5e9
pulse = np.sin(2 * np.pi * freq * n * dt)
Ez[src_x, src_y] += pulse
Limitations of this simple version

This is a teaching version, so it uses a very basic edge treatment.

That means:

boundary reflections are not fully removed
no PML is implemented
no conductivity loss yet
no PEC/PMC objects yet

For learning, it is very useful.
For research-grade work, you would usually add:

Mur absorbing boundary
PML
lossy materials
PEC masks
far-field extraction

## What you learn from this simulator

This 2D code helps you understand:

wavefront expansion in 2D
interaction with dielectric materials
field distributions in space and time
numerical discretization of Maxwell equations
the basis of larger tools like CST, HFSS, and custom FDTD solvers
```

---

## 🧭 Simulation Behavior

- Gaussian pulse is injected
- Wave propagates in 2D
- Interacts with dielectric region
- Reflection and transmission observed
- Field visualized as heatmap

---

## 🔧 Key Parameters

| Parameter | Description |
|----------|-------------|
| Nx, Ny | Grid size |
| dx, dy | Spatial resolution |
| dt | Time step (CFL condition) |
| Nt | Number of time steps |

---

## 🧱 Material Modeling

Example dielectric block:

```python
eps_r[50:80, 50:80] = 4.0
```

---

## ⚡ Source

Gaussian pulse:

```python
pulse = np.exp(-0.5 * ((n - t0) / spread) ** 2)
```

---

## 🧪 What You Can Modify

- Grid size
- Dielectric shape
- Source location
- Source type (sinusoidal)
- Material properties

---

## 📊 Outputs

- Ez field distribution
- Wave propagation over time
- Reflection and transmission patterns

---

## 🎥 Visualization

- Static field plots
- Animated EM wave propagation

---

## ⚠️ Limitations

- No PML boundary
- Simple absorbing edges
- No lossy media
- No PEC/PMC objects

---

## 🚀 Extensions

For advanced use:

- Add PML boundaries
- Implement lossy materials
- Add PEC objects
- Extract far-field patterns
- Extend to 3D FDTD

---

## 🧠 Learning Outcomes

- Understand 2D wave propagation
- Learn FDTD discretization
- Visualize EM field behavior
- Bridge to CST / HFSS tools

---

## ✅ Summary

This simulator provides a **clear and visual introduction to 2D computational electromagnetics**, forming the foundation for advanced EM modeling and CPS-integrated digital twin systems.
