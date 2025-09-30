from cProfile import label
import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("SB_lampe.csv", delimiter=",", dtype=str)
temp = [np.float32(i) for i in data[1:, -1]]
straalespenning_s = [np.float32(i) for i in data[1:, 2]]

k = 8.9e-9 
sigma = 5.67e-8
x_vals = np.arange(700, 2700, 100)
y_vals = [k*sigma*x**4 for x in x_vals]

error = 0.0006

plt.plot(temp, straalespenning_s, marker="o", markeredgecolor="none", markerfacecolor="red", linestyle="--", color="black")
plt.errorbar(temp, straalespenning_s, yerr=error, fmt="none", ecolor="black", capsize=5, capthick=2)
plt.plot(x_vals, y_vals, label="$k \sigma T^4 \\text{ hvor } k = 9\cdot 10^{-9}$")
plt.xlabel("temperatur (T) $[K]$")
plt.ylabel("strålespenning (U) $[V]$")
plt.tight_layout(pad=1.2)

plt.legend()
plt.show()