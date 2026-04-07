# NN to predict numbers x∈(0,1) from inputs 1-9.

from __future__ import annotations
import numpy as np
import matplotlib.pyplot as plt


sigmoid = lambda x: 1 / (1 + np.exp(-x))
relu = lambda x: np.maximum(0, np.minimum(x,1))


class Synapse:
    def __init__(self, input: Neuron | float, output: Neuron | float):
        self.input = input
        self.output = output
        self.weight = 0.0

    def update_weight(self, new_weight: float):
        self.weight = new_weight


class Neuron:
    def __init__(self, synapses: list[Synapse]):
        self.synapsis = synapses
    
    def update(self):
        for synapse in self.synapsis:
            synapse.update_weight(...)

    def transfer(self):
        inputs = self.synapsis



class NN:
    def __init__(self, nr_inputs: int, nr_outputs: int, layers: int, depth: int):
        pass
