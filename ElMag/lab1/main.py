import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

PATH_TO_DATA_FILE = "data.csv"
DATA_PERCISION = 10

# Constants
MEW_0 = 1.26e-6 # magnetic constant (T*m/A)


def get_data_csv(file_path):
    # TODO:
    pass

def magnetflukstetthet(x, N, I, R) -> int:
    """
    returns the magnetic flux density at position x given:
    x: position (m)
    N: number of turns in the coil
    I: current in the coil
    R: radius of the coil (m)
    """
    return (N*MEW_0*I)/(2*R) * (1 + x**2/R**2)**(-3/2)

def helmoholtzspoler(x, N, I, R, a) -> int:
    """
    returns the magnetic flux density at position x given:
    x: position (m)
    N: number of turns in the coil
    I: current in the coil (A)
    R: radius of the coil (m)
    a: distance between the coils (m)
    """
    return (N*MEW_0*I)/(2*R) * (1 + (x - a/2)**2/R**2)**(-3/2) + (N*MEW_0*I)/(2*R) * (1 + (x + a/2)**2/R**2)**(-3/2)

def målt_magnetflukstetthet(data) -> list:
    """
    returns the measured magnetic flux densities from the data
    """
    return [1, 2, 3] # TODO: get the correct data row

class Eksperiment:
    def __init__(self, PATH_TO_DATA_FILE, DATA_PERCISION):
        self.data_path = PATH_TO_DATA_FILE
        self.percission = DATA_PERCISION
        # self.data = get_data_csv(self.data_path)
        self.data = [1, 2, 3]
        # self.measured_magnetic_flux_density = målt_magnetflukstetthet(self.data)
        self.measured_magnetic_flux_density = [i for i in range(self.percission)]

    def make_table(self, func, x1, x2, N: int, I: int, R: int, a=None):
        """
        func: funksjonen som beregner 
        x1, x2 (m)
        N: antall vinklinger til spolen
        I: strømstyrken (A)
        R: gjennomsnitt spoleradius (m)
        a: avstand mellom spolene (m)
        """
        x_vals = np.linspace(x1, x2, self.percission)
        if a:
            beregnet_magnetflukstetthet = [func(x, N, I, R, a) for x in x_vals]
        else:
            beregnet_magnetflukstetthet = [func(x, N, I, R) for x in x_vals]

        d = {
            "Posisjon (cm):": x_vals,
            "Beregnet Magnetflukstettheten (T)": beregnet_magnetflukstetthet,
            "Målt Magnetflukstettheten (T)": self.measured_magnetic_flux_density,
            "Avvik (%)": [((b - m)/m)*100 for b, m in zip(beregnet_magnetflukstetthet, self.measured_magnetic_flux_density)]
        }
        df = pd.DataFrame(data=d)
        return [df, x_vals, d["Beregnet Magnetflukstettheten (T)"]]

    def kurvediagram(self, x, y):
        plt.plot(x, y)
        plt.show()



if __name__ == "__main__":

    exp1 = Eksperiment(PATH_TO_DATA_FILE, DATA_PERCISION)
    # R = 0.07
    # a = [R/2, R, 2*R]
    # data_frames = [
    #     exp1.make_table(helmoholtzspoler, -0.20, 0.20, 330, 1, 0.07, a=a[0]),
    #     exp1.make_table(helmoholtzspoler, -0.20, 0.20, 330, 1, 0.07, a=a[1]),
    #     exp1.make_table(helmoholtzspoler, -0.20, 0.20, 330, 1, 0.07, a=a[2])
    # ]
    # import functools as ft
    # df = ft.reduce(lambda left, right:
    #     pd.merge(left, right, on="name"), data_frames)



