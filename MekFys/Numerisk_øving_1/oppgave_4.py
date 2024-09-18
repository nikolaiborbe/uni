from math import sin, cos, pi
import matplotlib.pyplot as plt
import numpy as np

def angle_funk(A, theta):
    return A*sin(theta) + 0.1*theta  

def deriv_angel_funk(A, theta):
    return A*cos(theta) + 0.1

x_values = np.linspace(0, 2*pi, 40)
A = 2

y_values   = []
dy_values = []

for i in x_values:
    y_values.append(angle_funk(A, i))
    dy_values.append(deriv_angel_funk(A, i))

    
data = np.column_stack((x_values, y_values, dy_values))
np.savetxt("oppgave_4.csv", data, delimiter=",", header="x_values, y_values, dy_values")

imported_data = np.loadtxt("oppgave_4.csv", delimiter=",")
x_val, y_val, dy_val = imported_data[:,0], imported_data[:,1], imported_data[:,2]

plt.figure(1)
plt.xlabel(r"$\theta$")
plt.ylabel("Values")
plt.plot(x_val, y_val, "r", label=r"$f(\theta)$")
plt.plot(x_val, dy_val, "b", label=r"$f\'(\theta)$")
plt.legend()
plt.show()

