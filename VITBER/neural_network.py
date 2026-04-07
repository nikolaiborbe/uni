# NN to predict x∈(0,1) from inputs 1-9.

from __future__ import annotations
import numpy as np
import matplotlib.pyplot as plt

sigmoid = lambda x: 1 / (1 + np.exp(-x))
relu = lambda x: np.maximum(0, np.minimum(x,1))
squared = lambda x: np.pow(x, 2) 

BIAS = 0
LAYERS = 2
WIDTH = 3
AF = ACTIVATION_FUNCTION = squared


class Neuron:
    def __init__(self, weights: np.ndarray):
        self.W = weights
        self.output = np.zeros()

    def update(self, x: np.ndarray):
        z = self.W @ x
        a = AF(z)
        self.output = a
        return a

weights = np.array([[1, -3], [-2, 1]])
x = np.array([[3], [2]])
n1 = Neuron(weights)
n1.update(x)

n2 = Neuron(n1.output)

print(n2.output)


class NN:
    def __init__(self, nr_inputs: int, nr_outputs: int, layers: int, depth: int):
        pass
