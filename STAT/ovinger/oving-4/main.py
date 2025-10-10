import numpy as np
import matplotlib.pyplot as plt
import math

n = 10_000

N_x = np.random.normal(150, 5, n)
N_y = np.random.normal(200, 7, n)
N_theta = np.random.normal(0.9, 0.05, n)

N_a = 1/2 * N_x * N_y * np.sin(N_theta)

est_mu_a = np.sum(N_a) / len(N_a)
est_std_a = np.std(N_a)
print("mu_a: ", est_mu_a)
print("std_a: ", est_std_a)
# >>> mu_a:  11733.453649250418
# >>> std_a:  738.9178896299179

mu_a = 1/2 * 150 * 200 * math.sin(0.9)
std_a = 735

plt.hist(N_a, 100, label="Estimated", alpha=0.5, edgecolor="None", color="r")
plt.hist(np.random.normal(mu_a, std_a, n), 100, label="Calculated", alpha=0.5, edgecolor="None", color="b")
plt.legend()
plt.show()
