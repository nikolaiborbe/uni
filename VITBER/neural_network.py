# NN to predict x∈(0,1) from inputs 1-9.

from __future__ import annotations
import numpy as np
import matplotlib.pyplot as plt

sigmoid = lambda x: 1 / (1 + np.exp(-x))
relu = lambda x: np.maximum(0, np.minimum(x, 1))
squared = lambda x: np.pow(x, 2)

BIAS = 0
LAYERS = 2
WIDTH = 3
AF = ACTIVATION_FUNCTION = squared


class Layer:
    def __init__(self, weights: np.ndarray):
        self.W = weights
        self.output = np.array([])

    def update(self, x: np.ndarray):
        z = self.W @ x
        a = AF(z)
        self.output = a
        return a


x = np.array([[3]])
w1 = np.random.rand(3, 1)
w2 = np.random.rand(3, 3)
w3 = np.random.rand(3, 1)

l1 = Layer(w1)
l1.update(x)

l2 = Layer(w2.T)
l2.update(l1.output)

l3 = Layer(w3.T)
l3.update(l2.output)

print(l3.output)


class NN:
    def __init__(self, nr_inputs: int, nr_outputs: int, layers: int, depth: int):
        pass
