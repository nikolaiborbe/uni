import matplotlib.pyplot as plt
from math import sqrt, sin, cos
import numpy as np

# parmas
m = 1
k = 1
b = 0.5

t0 = 0
t1 = 20
dt = 0.01
times = np.arange(t0,t1,dt)
x0 = 2
v0 = 0
ans = []

x = np.zeros_like(times)
v = np.zeros_like(times)
x[0] = x0
v[0] = v0

for i in range(len(times)-1):
    a = -(b*v[i] + k*x[i])/m
    x[i+1] = x[i] + dt*v[i]
    v[i+1] = v[i] + dt*a

plt.plot(times, x)
plt.show()



