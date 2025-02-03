import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

N =330 #[]antallviklinger
I0 =1.0 #[A]strøm
mu_0 =4.0*np.pi*1e-7 #[H/m] permeabilitetitomtrom
R =0.07 #[m]radius
x0 =0.400 #[m]sentrumavspolen

def B_felt_kort_spole(x):
    prefaktor= N*mu_0*I0/(2*R)
    return prefaktor*(1.0 +(x/R)**2)**(-1.5)

def main():
    filnavn= 'kort_spole.csv'
    data =np.loadtxt(filnavn, delimiter=',')
    xe =data[:, 0]-x0   #posisjon,sentrertrundtx0
    Be =data[:, 1]      #m˚aledata

    #BeregnB-feltet
    xb =np.linspace(xe[0],xe[-1], 100)  #fleredatapunkter
    Bb =B_felt_kort_spole(xb)*1e4       #beregnetB-felt(Gauss)

    #Plotresultatene
    plt.plot(xb,Bb, label='Beregnet')
    plt.plot(xe,Be, '.',label='M˚aledata')
    plt.xlabel('Avstandfra senterav spolen(m)')
    plt.ylabel('Magnetfelt(Gauss)')
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    main()