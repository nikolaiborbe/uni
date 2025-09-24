import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt("SB_lampe.csv", delimiter=",", dtype=str)
temp = [np.float32(i) for i in data[1:, -1]]
straalespenning_s = [np.float32(i) for i in data[1:, 2]]

plt.plot(temp, straalespenning_s, marker="o", markeredgecolor="none", markerfacecolor="red", linestyle="--", color="black")
plt.xlabel("temperatur (T) $[K]$")
plt.ylabel("strålespenning (U) $[V]$")
plt.tight_layout(pad=1.2)

plt.legend()
plt.show()