import numpy as np
import matplotlib.pyplot as plt
import statsmodels.api as sm

x = np.array([-2.5, 0.5, 3.3, 2.6, -0.7, -4.6, 3.3, 0.8, 1.9,-0.5, 1.2, 3.8])
y = np.array([4.1, 7.2, 5.0, 7.9, 5.8, 4.9, 5.0, 5.9, 6.9, 4.8, 6.7, 3.2])

cov = np.cov(x,y)[0,1]
corr = cov/np.sqrt(np.var(x)*np.var(y))
print(corr)
print("nice")
print("ok")

# sm.qqplot(x, label="Mars")
# sm.qqplot(y, label="April")

plt.scatter(x,y)
plt.title(f"r = {corr}")
plt.show()
