import numpy as np

# Definerer funksjonen F
def F(xy):
    x, y = xy
    return np.array([
        x**2 + 3*x - y**2 - 3,    # F1(x, y)
        np.cos(x) + 2*y - 5       # F2(x, y)
    ])

# Definerer Jacobianen til F
def J(xy):
    x, y = xy
    return np.array([
        [2*x + 3, -2*y],   # Derivater av F1 med hensyn til x og y
        [-np.sin(x), 2]    # Derivater av F2 med hensyn til x og y
    ])

tol = 1e-4         # Toleranse for løsningen
max_iter = 100     # Maksimalt antall iterasjoner
xy = np.array([2.0, 2.7])  # Startpunktet (x0, y0)

# Newtons metode
for i in range(max_iter):
    f_val = F(xy)
    norm_f = np.linalg.norm(f_val)
    if norm_f < tol:
        break
    # Løs J(xy) * delta = -F(xy) for delta
    delta = np.linalg.solve(J(xy), -f_val)
    xy = xy + delta

# Resultater
print("Tilnærmet løsning (x, y) =", xy)
print("Antall iterasjoner:", i + 1)
print("Normen til F(x,y):", norm_f)
