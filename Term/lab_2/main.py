import numpy as np
import matplotlib.pyplot as plt

dt = 120      # s
c = 4200      # J/(kg K)
m = 4.0       # kg
P = 100.0     # W

t = np.arange(0, 22 + 2, 2, dtype=float)

Th_C = np.array([18,21,23,26,29,30,32,34,36,37,39,40], dtype=float)
Tc_C = np.array([16,15,14,12,11, 9, 7, 6, 4, 2, 1, 0], dtype=float)

dTh = np.diff(Th_C)
Q2 = c * m * dTh
Wc = P * dt
eps = Q2 / Wc
t_mid = t[:-1] + (dt/60)/2

dTc = np.diff(Tc_C)
eps_cold = -c * m * dTc / Wc

# Carnot på midtpunkter
Th_mid_K = (Th_C[:-1] + Th_C[1:]) / 2 + 273.15
Tc_mid_K = (Tc_C[:-1] + Tc_C[1:]) / 2 + 273.15
eps_carnot = Th_mid_K / (Th_mid_K - Tc_mid_K)

plt.figure()
plt.scatter(t, Th_C, marker="+", label="T_h (°C)")
plt.scatter(t, Tc_C, marker="x", label="T_c (°C)")
plt.xlabel("t (min)")
plt.ylabel("T (°C)")
plt.grid(True)
plt.legend()

plt.figure()
plt.plot(t_mid, eps, "o-", label="ε_E varm side")
plt.plot(t_mid, eps_cold, "s--", label="ε_E kald side")
plt.plot(t_mid, eps_carnot, "^:", label="ε_Carnot")
plt.xlabel("t (min)")
plt.ylabel("ε")
plt.grid(True)
plt.legend()

plt.show()
