import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

#const
m = 1 #kg
k = 1 #Nm^-1
b = 0.5 #N*s*m^-1
g = 9.81 #m/s^2

#functions
def df(x, v):
    dx_dt = v
    dv_dt = -(b/m)*v - (k/m)*x
    return dx_dt, dv_dt

def step(x, v, dt):
    dx_dt, dv_dt = df(x, v)
    x = dt*dx_dt + x
    v = dt*dv_dt + v
    return x, v

def _print(name, ℝ, data):
    print("\n" * 2)
    print(f"{name}: {ℝ} → [ℝ]")
    print("----------")
    for i, (d1, d2) in enumerate(zip(data[0], data[1])): 
        print(f"n_{i:<2}: {d1:>30} | {d2:>30}")

###
def main():
    t_0 = 0
    x_0 = 2
    v_0 = 0
    dt = 0.25 

    x = [x_0]
    v = [v_0]
    times = np.arange(t_0, 20,dt)
    for t in times:
        o1, o2 = step(x[-1], v[-1], dt)
        x.append(o1)
        v.append(o2)

    _print("data", "ℕ", [x, v])

    import time
    time.sleep(5)

    plt.plot(times, x[:-1]) 
    plt.plot(times, v[:-1])
    plt.grid(); plt.show()






if __name__ == "__main__":
    main()
