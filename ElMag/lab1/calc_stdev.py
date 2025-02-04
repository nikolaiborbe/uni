import statistics
import numpy as np

data = np.loadtxt("data/10sek_stdev.csv", delimiter=",", encoding="utf-8-sig")
y_vals = data[:, 1]/100 # data is 100x
print("Standard deviation: ", statistics.stdev(y_vals))