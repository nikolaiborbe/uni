import numpy as np
import pandas as pd

def calculate_inklinasjon(B_x, B_y, B_z):
    I = np.atan(B_z / np.sqrt(B_x**2 + B_y**2))
    return I

type Filepath = str

def print_ink(filepath: Filepath = "data.csv"):
    data = np.genfromtxt(filepath, delimiter=",", skip_header=1)
    B_y = data[:, 1]
    B_x = data[:, 2]
    B_z = data[:, 3]
    
    D = calculate_inklinasjon(B_x, B_y, B_z)
    
    mean_D = np.degrees(np.mean(D))
    std_D = np.degrees(np.std(D, ddof=1))
    relative_uncertainty = std_D / abs(mean_D)
    
    print(f"Inklinasjon (mean) = {mean_D:.4f}°")
    print(f"Standard deviation = ±{std_D:.4f}°")
    print(f"Relative uncertainty = {relative_uncertainty:.4%}")

if __name__ == "__main__":
    print_ink("data.csv")

