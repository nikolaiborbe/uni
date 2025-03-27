import numpy as np
import pandas as pd 

def calculate_deklinasjon(B_x, B_y):
    # Calculate deklinasjon (in radians) for each measurement
    D = np.arctan(B_y / B_x)
    return D

type Filepath = str

def print_dek(filepath: Filepath = "data.csv"):
    # Load data from CSV.
    # The CSV is assumed to have a header and columns: index, B_x, B_y (and possibly more)
    # Adjust delimiter and column indices as needed.
    data = np.genfromtxt(filepath, delimiter=",", skip_header=1)
    B_y = data[:, 1]
    B_x = data[:, 2]
    
    # Calculate deklinasjon for each measurement
    D = calculate_deklinasjon(B_x, B_y)
    
    # Compute mean, standard deviation, and relative uncertainty
    mean_D = np.degrees(np.mean(D))
    std_D = np.degrees(np.std(D, ddof=1))
    relative_uncertainty = std_D / abs(mean_D)
    
    print(f"Deklinasjon (mean) = {mean_D:.4f}°")
    print(f"Standard deviation = ±{std_D:.4f}°")
    print(f"Relative uncertainty = {relative_uncertainty:.4%}")

if __name__ == "__main__":
    print_dek("data.csv")
