import matplotlib.pyplot as plt
import numpy as np

# Oppgave a
temps = np.arange(86, 287, 40)
a = 1.37
b = 0.0387
N = 100

def p(V, T):
    R = 8.3144
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

for i in range(len(pressures)):
    plt.plot(volumes, pressures[i], label=f"Temperatur: {temps[i]} [K]")
plt.plot(volumes, [p_ideel(v) for v in volumes], label="Ideel gass ved T = 286 K", color="black")
plt.xlabel("Volum $V$ [L]")
plt.xscale("log")
plt.ylabel("Trykk $p$ [bar]")
plt.legend()
plt.show()

# Oppgave b
 
