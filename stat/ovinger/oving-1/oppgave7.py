
import numpy as np
import matplotlib.pyplot as plt
# Sett hvilke x-verdier du vil plotte for
x = np.linspace(0,5,100)
# Sett verdien for parameteren alpha
alpha = 1
# Beregn kumulativ fordelingsfunksjon
def F_X(x, alpha):
    return 1- np.exp(-x**2/alpha)

# a)
# 1)
h = 0.001
f_x = lambda x,a: (F_X((x+h), a) - F_X(x, a)) / h

# b) 
def P_levetid(x):
    return 4*x*np.e**(-2*x**2)*(np.e**x**2 - 1)*x


plt.plot(x, f_x(x, alpha), color="red")
plt.plot(x, P_levetid(x), color="blue")
plt.xlabel("x")
plt.ylabel("F(x)")
plt.show()