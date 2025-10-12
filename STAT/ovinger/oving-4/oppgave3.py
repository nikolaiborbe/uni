import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm

lam = 12
r = 1000
n = 42
m = 35

alpha = 2*n / (2*n + m)
beta = 2*m / (2*n + m)

X= np.random.poisson(lam, r)
Y = np.random.poisson(lam/2, r)

sim_estimator = alpha*X + beta*Y
print(sim_estimator)
print(np.average(sim_estimator))

plt.hist(sim_estimator, bins=25)
plt.show()

sm.qqplot(sim_estimator)
plt.show()