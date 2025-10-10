import matplotlib.pyplot as plt
import numpy as np

# Oppgave a
temps = np.arange(86, 287, 40)
R = 8.3144
N = 100

# N_2 egenskaper
a = 1.37
b = 0.0387
C_p = 1.04

def p(V, T):
    # tror kanskje jeg trenger antall mol n
    return (R*T)/(V-b) - a/V**2

def p_ideel(V):
    R = 8.3144
    T = 286
    # tror kanskje jeg trenger antall mol n
    return (R*T)/V

volumes = np.linspace(0.06, 0.6,len(temps))

pressures = []
for T in temps:
    pressures.append([p(v, T) for v in volumes])

# for i in range(len(pressures)):
#     plt.plot(volumes, pressures[i], label=f"Temperatur: {temps[i]} [K]")
# plt.plot(volumes, [p_ideel(v) for v in volumes], label="Ideel gass ved T = 286 K", color="black")
# plt.xlabel("Volum $V$ [L]")
# plt.xscale("log")
# plt.ylabel("Trykk $p$ [bar]")
# plt.legend()
# plt.show()

# Oppgave b
T = np.arange(1,100, 1)
p = np.arange(1,100, 1)
V_ideell = R*T/p
V_gammel = V_ideell
for i in range(1, 30, 1):
    V_ny = b + R*T/(p+a/V_gammel**2)
    V_gammel = V_ny
print(V_ny)

# def mu_jt(T, p):
#         if (R*T/C_p)/(p + a/V**2 - 2*a*(V-b)/V**3) - V/C_p:
 
