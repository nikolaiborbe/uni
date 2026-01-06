import numpy as np
""" import matplotlib.pyplot as plt """

#utfallsrom
x=np.arange(6)

#punktsannsynlighet
f_x = np.array([0.05,0.10,0.25,0.40,0.15,0.05])

# === oppgave 1 ===
# a)
P_leq_two = sum(f_x[:3]) # >> 0.4

# b)
P_le_four = sum(f_x[:4])
snitt_b = P_leq_two
P_leq_two_given_P_le_four = snitt_b/P_le_four # >> 0.5

# c)
P_geq_one = sum(f_x[1:])
snitt_c = sum(f_x[1:3])
P_leq_two_given_P_geq_one = snitt_c/P_geq_one # >> 0.368421 

# === oppgave 2 ===
F_x = lambda x: sum(f_x[:x])

""" 
#stolpediagram
plt.bar(x, f_x)
plt.xlabel("x")
plt.ylabel("f(x)")
plt.title("Stolpediagram for f(x)")
plt.show()
 """
