import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import math

def dek(B_y, B_x):
    return np.atan(B_y/B_x)

def ink(B_z, B_x, B_y):
    R = np.sqrt(B_x**2 + B_y**2)
    u = B_z / R
    ink = np.atan(u)
    factor = 1/(1 + u**2)

    dB_z = factor * 1/R
    dB_x = factor * (-B_z*B_x)/R**3
    dB_y = factor * (-B_z*B_y)/R**3

    std = np.sqrt(dB_z**2 * np.std(B_z)**2 + dB_x**2 * np.std(B_x)**2 + dB_y**2 * np.std(B_y)**2)

    return ink, std


def main():
    # df = pd.read_csv("data.csv", delimiter=",").dropna()

    data = np.genfromtxt("data.csv", delimiter=",", skip_header=True)
    B_x = data[:, 1]
    B_y = data[:, 2]
    B_z = data[:, 3]

    inkli = ink(B_z, B_x, B_y)
    print(f"Inklinasjon {np.average(inkli[0])} ± {np.average(inkli[1])}")

if __name__ == "__main__":
    main()

