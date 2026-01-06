import numpy as np

def simX(n):
    x = np.zeros(n)
    for i in range(n):
        u = np.random.uniform()
        if u <= 0.167:
            x[i] = 3
        elif u <= 0.528:
            x[i] = 4
        elif u <= 0.956:
            x[i] = 5
        else:
            x[i] = 6
    return x

N = 10_000 # <- vi har bare 4 "bøtter" med verdier, så f(x) konvergerer raskt mot et riktig histogram.
vals = simX(N)
# vals_squared = vals**2
# ev = np.average(vals_squared)
ev = np.sum(vals**2)/N
print(ev)
