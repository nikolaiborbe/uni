import matplotlib.pyplot as plt
import numpy as np

fixed_points = np.array([[0. ,0.]])
epsilon = 0.5

y = np.linspace(-3, 3, 100)
z = np.linspace(-6, 3, 100)

Y, Z = np.meshgrid(y, z)

Ydot = Z
Zdot = 1 / epsilon * (Y * Z - Y)

fix, ax = plt.subplots()
ax.streamplot(Y, Z, Ydot, Zdot, color="black", linewidth=0.5)
ax.set_xlabel("y")
ax.set_ylabel("z", rotation=0)
plt.axhline(y=0, color="black", linewidth="0.5")
plt.axvline(x=0, color="black", linewidth="0.5")

plt.show()
