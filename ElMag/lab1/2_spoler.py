import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

N =330 #[]antallviklinger
I0 =1.0 #[A]strøm
mu_0 =4.0*np.pi*1e-7 #[H/m] permeabilitetitomtrom
R =0.07 #[m]radius

def B_felt_kort_spole(x):
    prefaktor= N*mu_0*I0/(2*R)
    return prefaktor*(1.0 +(x/R)**2)**(-1.5)

def main():
    data1 =np.loadtxt("data/data1.csv", delimiter=',', encoding="utf-8-sig", skiprows=1, usecols=(0,1))

    xe1 =data1[:, 0]   #posisjon
    Be1 =data1[:, 1]   #måledata

    #Plotresultatene
    plt.plot(xe1,Be1, label='Måledata')
    plt.xlabel('Avstandfra senterav spolen(m)')
    plt.ylabel('Magnetfelt(Gauss)')
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    main()