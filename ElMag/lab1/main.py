import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

PATH_TO_DATA_FILE = "data.csv"

# Constants
MEW_0 = 1.26e-6 # magnetic constant (T*m/A)


def get_data_csv(file_path):
    # TODO:
    pass

def magnetflukstetthet(x, N, I, R) -> int:
    return (N*MEW_0*I)/(2*R) * (1 + x**2/R**2)**(-3/2)

def anti_helmoholtzspoler(x, N, I, R, a) -> int:
    # TODO: could be + & + maybe?
    return (N*MEW_0*I)/(2*R) * (1 + (x - a/2)**2/R**2)**(-3/2) + (N*MEW_0*I)/(2*R) * (1 + (x - a/2)**2/R**2)**(-3/2)


def helmoholtzspoler(x, N, I, R, a) -> int:
    return (N*MEW_0*I)/(2*R) * (1 + (x - a/2)**2/R**2)**(-3/2) + (N*MEW_0*I)/(2*R) * (1 + (x + a/2)**2/R**2)**(-3/2)

def målt_magnetflukstetthet_b1(data) -> list:
    """
    returns the measured magnetic flux densities from the data
    """
    return [1, 2, 3] # TODO: get the correct data row


class Eksperiment1:
    def __init__(self, N=100):
        self.data_path = PATH_TO_DATA_FILE
        # self.data = get_data_csv(self.data_path)
        # self.measured_magnetic_flux_density = målt_magnetflukstetthet(self.data)
        self.measured_magnetic_flux_density = [i for i in range(N)]
        self.data = []

    def add_data(self, data):
        self.data.append(data)

    def make_table(self, x1=-.20, x2=.20, I=1, R=0.07, N=100):
        x_vals = np.linspace(x1, x2, N)
        beregnet_magnetflukstetthet = [magnetflukstetthet(x, N, I, R) for x in x_vals]

        d = {
            "Posisjon (cm):": x_vals,
            "Beregnet Magnetflukstettheten (T)": beregnet_magnetflukstetthet,
            **{f"Målt Magnetflukstettheten (T) ({i})": self.data[i] for i in range(len(self.data))},
            **{f"Avvik (%) ({i})": [((b - m)/m)*100 for b, m in zip(beregnet_magnetflukstetthet, self.data[i])] for i in range(len(self.data))}
        }
        df = pd.DataFrame(data=d)
        print(df)
    
class Eksperiment2:
    def __init__(self, N=100):
        self.data_path = PATH_TO_DATA_FILE
        # self.data = get_data_csv(self.data_path)
        self.data = [1, 2, 3]
        # self.measured_magnetic_flux_density = målt_magnetflukstetthet(self.data)
        self.measured_magnetic_flux_density = [i for i in range(N)]
        self.data = []

    def add_data(self, data):
        self.data.append(data)

    def make_table(self, x1, x2, I: int, R: int, N=100):
        x_vals = np.linspace(x1, x2, N)
        y1 = [helmoholtzspoler(x, N, I, R, 2*R) for x in x_vals]
        y2 = [helmoholtzspoler(x, N, I, R, R) for x in x_vals]
        y3 = [helmoholtzspoler(x, N, I, R, R/2) for x in x_vals]

        d = {
            "Posisjon (cm):": x_vals,
            "a = 2R, Beregnet Magnetflukstettheten (T)": y1,
            "a = R, Beregnet Magnetflukstettheten (T)": y2,
            "a = R/2, Beregnet Magnetflukstettheten (T)": y3
            # "Målt Magnetflukstettheten (T)": self.measured_magnetic_flux_density,
            # "Avvik (%)": [((b - m)/m)*100 for b, m in zip(beregnet_magnetflukstetthet, self.measured_magnetic_flux_density)]
        }
        df = pd.DataFrame(data=d)
        y_vals = [y1, y2, y3]
        return df, x_vals, y_vals

class Eksperiment3:
    def __init__(self, N=100):
        self.data_path = PATH_TO_DATA_FILE
        # self.data = get_data_csv(self.data_path)
        self.data = [1, 2, 3]
        # self.measured_magnetic_flux_density = målt_magnetflukstetthet(self.data)
        self.measured_magnetic_flux_density = [i for i in range(N)]
        self.data = []

    def add_data(self, data):
        self.data.append(data)
    
    def make_table(self, x1, x2,  I: int, R: int, N=100):
        x_vals = np.linspace(x1, x2, N)
        y1 = [anti_helmoholtzspoler(x, N, I, R, 2*R) for x in x_vals]
        y2 = [anti_helmoholtzspoler(x, N, I, R, R) for x in x_vals]
        y3 = [anti_helmoholtzspoler(x, N, I, R, R/2) for x in x_vals]

        d = {
            "Posisjon (cm):": x_vals,
            "a = 2R, Beregnet Magnetflukstettheten (T)": y1,
            "a = R, Beregnet Magnetflukstettheten (T)": y2,
            "a = R/2, Beregnet Magnetflukstettheten (T)": y3
            # "Målt Magnetflukstettheten (T)": self.measured_magnetic_flux_density,
            # "Avvik (%)": [((b - m)/m)*100 for b, m in zip(beregnet_magnetflukstetthet, self.measured_magnetic_flux_density)]
        }
        df = pd.DataFrame(data=d)
        y_vals = [y1, y2, y3]
        return df, x_vals, y_vals

if __name__ == "__main__":
    exp1 = Eksperiment1(N=5)
    exp1.add_data([1, 2, 3, 4, 1])
    exp1.add_data([3, 2, 1, 5,1 ])
    exp1.add_data([1, 4, 1, 5, 1])
    exp1.make_table()
