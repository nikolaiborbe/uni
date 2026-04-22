import matplotlib.pyplot as plt
import numpy as np

fixed_points = np.array([[0. ,0.]])
fig, ax = plt.subplots(1, 2)

y = np.linspace(-3, 3, 100)
z = np.linspace(-4, 3, 100)

Y, Z = np.meshgrid(y, z)

Ydot = Z
epsi = 1.0
Zdot = 1 / epsi * (Y * Z - Y)

ax[0].streamplot(Y, Z, Ydot, Zdot, color="black", linewidth=0.2)
ax[0].set_xlabel("y")
ax[0].set_ylabel("z", rotation=0)
ax[0].axhline(y=0, color="black", linewidth="0.5")
ax[0].axvline(x=0, color="black", linewidth="0.5")
ax[0].set_title(f"$\epsilon = 1$")

epsi = 0.01
Zdot = 1 / epsi * (Y * Z - Y)

ax[1].streamplot(Y, Z, Ydot, Zdot, color="black", linewidth=0.2)
ax[1].set_xlabel("y")
ax[1].set_ylabel("z", rotation=0)

ax[1].axhline(y=0, color="black", linewidth="0.5")
ax[1].axvline(x=0, color="black", linewidth="0.5")
ax[1].set_title(f"$\epsilon = 0.01$")

plt.show()
