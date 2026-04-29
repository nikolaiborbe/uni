from typing import Any
import numpy as np

# data = np.array([[1, 1], [2, 2], [3, 3], [0, 0], [5, 5], [2, 2]]) # training data (x, y)

W = np.array([[1,-3],[-2,1]])
x = np.array([3, 2]).T
y = target = 1
b_1, b_2 = np.array([0, 0]), np.array([0])
w = np.array([2,-1])

def sigmoid(z: np.ndarray) -> Any:
    return 1 / (1 + np.exp(-z))


# First pass

a_1 = sigmoid(np.einsum("jk, k->j", W, x) + b_1)
a_L = sigmoid(np.einsum("j,j->", w, a_1) + b_2)

# Calculate cost function





#find a
