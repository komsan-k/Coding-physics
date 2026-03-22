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
