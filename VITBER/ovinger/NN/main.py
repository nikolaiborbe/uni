from typing import Any
import numpy as np

# data = np.array([[1, 1], [2, 2], [3, 3], [0, 0], [5, 5], [2, 2]]) # training data (x, y)

W = np.array([[1,-3],[-2,1]])
x = np.array([3, 2]).T
y = target = 1
b_1, b_2 = np.array([0, 0]), np.array([0])
w = np.array([2,-1])

def Sigmoid(z: np.ndarray) -> Any:
    return 1 / (1 + np.exp(-z))

def d_Sigmoid(z: np.ndarray) -> Any:
    return np.exp(-z) / (1 + np.exp(-x))**2


# First pass

z_1 = np.einsum("jk, k->j", W, x) + b_1
a_1 = Sigmoid(z_1)

z_L = np.einsum("j,j->", w, a_1) + b_2
a_L = Sigmoid(z_L)

δ_L = -(y - a_L)*d_Sigmoid(z_L)
print(δ_L)





#find a
