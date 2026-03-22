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
