import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D  # registers the 3D projection

# Define the function
def f(x, y):
    return x**2 * y - y**2

# Create a grid for x and y
x = np.linspace(-1, 1, 400)
y = np.linspace(-1/np.sqrt(5), 1/np.sqrt(5), 400)
X, Y = np.meshgrid(x, y)

# Compute the function values
Z = f(X, Y)

# Create a mask for the elliptical region: x^2 + 5y^2 <= 1
mask = (X**2 + 5*Y**2) <= 1

# Set points outside the ellipse to NaN so they won't be plotted
Z_masked = np.where(mask, Z, np.nan)

# Create a 3D plot
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(X, Y, Z_masked, cmap='viridis', edgecolor='none')

# Add labels, title, and a color bar
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('f(x, y)')

# Adjust the subplot parameters to reduce padding
plt.subplots_adjust(left=0.05, right=0.95, top=0.95, bottom=0.05)

plt.show()
