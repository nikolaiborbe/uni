import matplotlib.pyplot as plt
import numpy as np

# Oppgave a
temps = np.arange(86, 287, 40)
R = 0.08314
N = 100

# N_2 egenskaper
a = 1.37
b = 0.0387
C_p = 1.04

def p(V, T):
    return (R*T)/(V-b) - a/V**2

def p_ideel(V):
    T = 286
    return (R*T)/V

volumes = np.linspace(0.06, 0.6,100)

pressures = []
for T in temps:
    pressures.append([p(v, T) for v in volumes])

for i in range(len(pressures)):
    plt.plot(volumes, pressures[i], label=f"Temperatur: {temps[i]} [K]")
plt.plot(volumes, [p_ideel(v) for v in volumes], label="Ideel gass ved T = 286 K", color="black")
plt.xlabel("Volum $V$ [L]")
plt.xscale("log")
plt.ylabel("Trykk $p$ [bar]")
plt.legend()
plt.show()

# Oppgave b
T0 = 2*a / (R*b)
T = np.linspace(T0/9, T0, 40)
p = np.linspace(10e5, 310e5, 40)
R = 8.314
a = 0.137
b = 3.87E-5
C_p = 7/2 * R
T_inv = np.linspace(T0 / 9, T0, 200)
p_inv = (a / b**2) * (-3 * T_inv /  T0 + 4*np.sqrt(T_inv / T0)-1)

TT, pp = np.meshgrid(T, p)

V = R*TT/pp
for _ in range(50):
    V = b + R*TT/(pp + a/(V**2))

def mu_jt(TT, pp, V):
    denom = pp + a/(V**2) - 2*a*(V - b)/(V**3)
    return (R*TT/C_p)/denom - V/C_p

with np.errstate(divide='ignore', invalid='ignore'):
    mu = mu_jt(TT, pp, V)
    mu[~np.isfinite(mu)] = np.nan


mu_bar = mu*1e5
zmin, zmax = -0.2, 0.2

fig, ax = plt.subplots(figsize=(0,6))
im = ax.imshow(mu_bar, origin="lower", extent=[T.min(), T.max(), p.min()/1e5, p.max()/1e5], vmin=zmin, vmax=zmax)
ax.set_ylabel("Trykk $p$ [bar]")
ax.set_xlabel("Temperatur $T$ [K]")
ax.plot(T_inv, p_inv * 1e-5, lw=2)
plt.show()