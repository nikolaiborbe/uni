"""Pre-lab 1.2: Fresnel equations at air-water interface"""
import numpy as np
import matplotlib.pyplot as plt

n1, n2 = 1.0, 1.334  # air, water
theta = np.linspace(0, 89, 500)  # degrees
t = np.deg2rad(theta)

# Snell's law to get transmitted angle
cos_t2 = lambda ni, nt, ti: np.sqrt(1 - (ni/nt * np.sin(ti))**2 + 0j)

# Fresnel amplitude coefficients
def fresnel(ni, nt, ti):
    ct1, ct2 = np.cos(ti), cos_t2(ni, nt, ti)
    r_TE = (ni*ct1 - nt*ct2) / (ni*ct1 + nt*ct2)
    r_TM = (nt*ct1 - ni*ct2) / (nt*ct1 + ni*ct2)
    return np.real(r_TE), np.real(r_TM)

# External (air->water) and internal (water->air)
r_TE_ext, r_TM_ext = fresnel(n1, n2, t)
r_TE_int, r_TM_int = fresnel(n2, n1, t)

# Brewster angles
brewster_ext = np.rad2deg(np.arctan(n2/n1))
brewster_int = np.rad2deg(np.arctan(n1/n2))
critical = np.rad2deg(np.arcsin(n1/n2))

print(f"External (air->water): Brewster = {brewster_ext:.1f}°")
print(f"Internal (water->air): Brewster = {brewster_int:.1f}°, Critical = {critical:.1f}°")

# Plot
fig, ax = plt.subplots(1, 2, figsize=(12, 5))

ax[0].plot(theta, r_TE_ext, label='TE'); ax[0].plot(theta, r_TM_ext, label='TM')
ax[0].axvline(brewster_ext, ls='--', c='g', label=f'Brewster={brewster_ext:.1f}°')
ax[0].set_title('External (air → water)'); ax[0].legend(); ax[0].grid()

ax[1].plot(theta, r_TE_int, label='TE'); ax[1].plot(theta, r_TM_int, label='TM')
ax[1].axvline(brewster_int, ls='--', c='g', label=f'Brewster={brewster_int:.1f}°')
ax[1].axvline(critical, ls=':', c='purple', label=f'Critical={critical:.1f}°')
ax[1].set_title('Internal (water → air)'); ax[1].legend(); ax[1].grid()

for a in ax: a.set_xlabel('Angle (°)'); a.set_ylabel('r')
plt.tight_layout(); plt.savefig('fresnel.pdf'); plt.show()

# Reflectance R and Transmittance T
R_TE_ext, R_TM_ext = r_TE_ext**2, r_TM_ext**2
R_TE_int, R_TM_int = np.abs(fresnel(n2, n1, t)[0])**2, np.abs(fresnel(n2, n1, t)[1])**2

fig, ax = plt.subplots(1, 2, figsize=(12, 5))
ax[0].plot(theta, R_TE_ext, label='R_TE'); ax[0].plot(theta, R_TM_ext, label='R_TM')
ax[0].set_title('External: R'); ax[0].legend(); ax[0].grid()
ax[1].plot(theta, R_TE_int, label='R_TE'); ax[1].plot(theta, R_TM_int, label='R_TM')
ax[1].set_title('Internal: R'); ax[1].legend(); ax[1].grid()
for a in ax: a.set_xlabel('Angle (°)'); a.set_ylabel('R')
plt.tight_layout(); plt.savefig('fresnel_R.pdf'); plt.show()
