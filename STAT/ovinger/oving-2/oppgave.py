import numpy as np
import matplotlib.pyplot as plt


x = np.arange(0, 6)
y = [0.05, 0.1, 0.25, 0.4, 0.15, 0.05]


class Opg1:
    def __init__(self):
        # opg 1:
        p_x_leq_two = sum(y[:3]) / sum(y)
        print(p_x_leq_two)  # >>> 0.4

        # opg 2:
        # UTLEVERT KODE (ingenting her skal endres)
        f_x = np.array([0.05, 0.10, 0.25, 0.40, 0.15, 0.05])
        F_x = [np.sum(f_x[:i]) for i in range(1, 7)]

        def simX(n):
            # verdimengde
            x = np.arange(6)
            # for lagring av realisasjoner
            x_sim = np.zeros(n)
            for i in range(n):  # vi simulerer hver og en x for seg
                u = np.random.uniform()  # en realisasjon fra U(0,1)
                if u < F_x[0]:  # hvis u er mindre enn den laveste
                    # verdien i F_x vil
                    # vi at realisasjonen skal være 0
                    x_sim[i] = x[0]
                elif u <= F_x[1]:
                    x_sim[i] = x[1]
                elif u <= F_x[2]:
                    x_sim[i] = x[2]
                elif u <= F_x[3]:
                    x_sim[i] = x[3]
                elif u <= F_x[4]:
                    x_sim[i] = x[4]
                elif u > F_x[4]:
                    x_sim[i] = x[5]
            return x_sim

        n = 1000
        # Simuler realisasjoner av X ved å kalle på simX-funksjonen i cellen over
        simulerte_X = simX(n)

        # Approksimer sannsynligheten
        P_X_le_2 = len(list(filter(lambda x: x <= 2, simulerte_X))) / n

        # Skriv ut resultatet
        print("Approksimert sannsynlighet: ", P_X_le_2)  # >>> 0.382


class Opg2:
    def __init__(self):
        f_x = np.array([0.05, 0.10, 0.25, 0.40, 0.15, 0.05])
        E_x = sum([i * f_x[i] for i in range(len(f_x))]) # >>> 2.650

        Var_X = sum([f_x[i] * (i - E_x)**2 for i in range(len(f_x))]) # >>> 1.327

        Std_X = np.sqrt(Var_X) # >>> 1.152


        F_x = [np.sum(f_x[:i]) for i in range(1, 7)]
        def simX(n):
            # verdimengde
            x = np.arange(6)
            # for lagring av realisasjoner
            x_sim = np.zeros(n)
            for i in range(n):  # vi simulerer hver og en x for seg
                u = np.random.uniform()  # en realisasjon fra U(0,1)
                if u < F_x[0]:  # hvis u er mindre enn den laveste
                    # verdien i F_x vil
                    # vi at realisasjonen skal være 0
                    x_sim[i] = x[0]
                elif u <= F_x[1]:
                    x_sim[i] = x[1]
                elif u <= F_x[2]:
                    x_sim[i] = x[2]
                elif u <= F_x[3]:
                    x_sim[i] = x[3]
                elif u <= F_x[4]:
                    x_sim[i] = x[4]
                elif u > F_x[4]:
                    x_sim[i] = x[5]
            return x_sim
        
        n = 1000
        simulterte_X = simX(n)

        sim_E_X = np.average(simulterte_X) # >>> 2.66
        sim_Std_X = np.sqrt((1/(len(simulterte_X) - 1) * sum([(x - sim_E_X)**2 for x in simulterte_X]))) # >>> 1.139

class Opg3:
    def __init__(self):


o = Opg3()
