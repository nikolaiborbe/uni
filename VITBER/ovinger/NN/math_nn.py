import numpy as np


x = np.array([[3], [2]])
W = np.array([[1, -3], [-2, 1]])
w = np.array([[2], [-1]])

z1 = W @ x
a1 = np.pow(z1, 2)

z2 = w.T @ a1
a2 = np.pow(z2, 2)