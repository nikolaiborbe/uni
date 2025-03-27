import numpy as np

def f(p):
    x = p[0]; y = p[1]
    f_x = x**2 + 3*x - y**2 - 3
    f_y = np.cos(x) + 2*y - 5
    return [f_x, f_y]


def df(p):
    x = p[0]; y = p[1]
    return np.array([
        [2*x + 3, -2*y],
        [-np.sin(x), 2],
        ])
    

def FLV_newton(x0, f, df, ε):
    x = None
    Δ = np.linalg.norm(f(x0))

    i = 0
    while Δ > ε:
        dfI = np.linalg.inv(df(x0))
        x   = x0 - np.matmul(dfI, f(x0))
        Δ   = np.linalg.norm(f(x))
        x0  = x
        i += 1

    return x, i


ε  = 1e-4
x0 = np.array([1.5, 2.5])
x, i  = FLV_newton(x0, f, df, ε)

print(f"NM: {x}, med {i} iterasjoner")
