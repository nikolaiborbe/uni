import numpy as np
import matplotlib.pyplot as plt

# constants
m = 1.0
k = 1.0
b = 0.5

def derivative(x, v):
    """
    Returns (dx/dt, dv/dt) for the damped oscillator
    """
    dx_dt = v
    dv_dt = -(b/m)*v - (k/m)*x
    return dx_dt, dv_dt

def euler_step(x, v, dt):
    """
    Euler update for x, v
    """
    dx_dt, dv_dt = derivative(x, v)
    x_new = x + dx_dt * dt
    v_new = v + dv_dt * dt
    return x_new, v_new

def main():
    # initial conditions
    x = 2.0
    v = 0.0
    t0, t1 = 0.0, 20.0
    dt = 0.01  # pick a suitable step
    nsteps = int((t1 - t0)/dt)

    xs = []
    ts = []
    
    current_time = t0
    for _ in range(nsteps):
        xs.append(x)
        ts.append(current_time)
        x, v = euler_step(x, v, dt)
        current_time += dt

    plt.plot(ts, xs)
    plt.xlabel("time (s)")
    plt.ylabel("x (m)")
    plt.title("Damped harmonic oscillator (Euler method)")
    plt.show()

if __name__ == "__main__":
    main()
