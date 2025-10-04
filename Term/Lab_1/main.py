import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("SB_lampe.csv", delimiter=",", dtype=str)
temp = [np.float32(i) for i in data[1:, -1]]
straalespenning_s = [np.float32(i) for i in data[1:, 2]]

k = 8.85e-9 
sigma = 5.67e-8
x_vals = np.arange(700, 2700, 100)
y_vals = [k*sigma*x**4 for x in x_vals]

yerror = 0.0006

plt.plot(temp, straalespenning_s, marker="o", markeredgecolor="none", markerfacecolor="red", linestyle="--", color="black")
plt.errorbar(temp, straalespenning_s, yerr=yerror, fmt="none", ecolor="black", capsize=5, capthick=2)
plt.plot(x_vals, y_vals, label="$k \sigma T^4 \\text{ hvor } k = 8.85\cdot 10^{-9}$")
plt.xlabel("temperatur (T) $[K]$", fontsize=18)
plt.ylabel("strålespenning (U) $[V]$", fontsize=18)
plt.xticks(fontsize=16)
plt.yticks(fontsize=16)
#plt.tight_layout(pad=1.1)

plt.legend(fontsize=20, fancybox=True)
plt.show()