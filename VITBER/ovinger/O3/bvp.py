import numpy as np
import scipy as sp
import matplotlib.pyplot as plt

def bvp_extended(y: np.ndarray, t, epsilon=1):
    """
    Solver for a BVP.

    Args:
        y (np.ndarray): Array of shape (4,) 
        t: _ 
        epsilon (int): 
    """
    return np.array(
        [
            y[1], 
            1/epsilon*(y[0]*y[1]-y[0]), 
            y[3], 
            1/epsilon*(y[2]*(y[1]-1)+y[3]*y[0])
        ]
    )


def F(s: float, epsilon=1):
    ya, yb = 1, -1 # randverdier
    y0 = [ya, s, 0, 1] # initialverdi til ivp-løser
    t0, t1 = 0, 1
    sol = sp.integrate.solve_ivp(
        fun=lambda t, y: bvp_extended(y, t, epsilon),
        t_span=(t0, t1),
        y0=y0,
        method='Radau',
        atol=1e-10
    )

    return (
        sol.y[0,-1]-yb, 
        sol.y[2,-1]
    )

fig, ax = plt.subplots(1, 2)

n = np.arange(0,5)
x = np.zeros(np.size(n))
y = np.zeros(2*np.size(n)).reshape(-1,2)
x[0] = x0 = 0
y[0] = F(x[0])

for i in range(1, len(n)): # 10 steps of newtons method
    x[i] = x[i-1] - y[i-1][0]/y[i-1][1]
    y[i] = F(x[i])

ax[0].plot(n, y[:,0], color="black", marker="+", label="$\epsilon = 1$")
ax[0].set_xlabel("Steg")
ax[0].set_ylabel("Feil i $y$", rotation=0, labelpad=20)
ax[0].set_title("Newton iterasjoner (skytemetoden)")
ax[0].legend()

epsilon_values = [1, 0.1, 0.05, 0.01]
for epsi in epsilon_values:
    n = np.arange(0,50)
    x = np.zeros(np.size(n))
    y = np.zeros(2*np.size(n)).reshape(-1,2)
    x[0] = 0
    y[0] = F(x[0], epsilon=epsi)

    for i in range(1, len(n)): # 10 steps of newtons method
        x[i] = x[i-1] - y[i-1][0]/y[i-1][1]
        y[i] = F(x[i], epsilon=epsi)

    ax[1].plot(n, y[:,0], label=f"$\epsilon$ = {epsi}", marker="+")

ax[1].set_title("Newton iterasjoner (skytemetoden) med forskjellige $\epsilon$")
ax[1].set_xlabel("Steg")
ax[1].set_ylabel("Feil i $y$", rotation=0, labelpad=20)
ax[1].legend()
plt.show()

