import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

N =330 #[]antallviklinger
I0 =1.0 #[A]strøm
mu_0 =4.0*np.pi*1e-7 #[H/m] permeabilitetitomtrom
R =0.07 #[m]radius
x0 =0.400 #[m]sentrumavspolen

def Helmholtzspoler(x, a):
    return (N*mu_0*I0)/(2*R) * (1 + (x - a/2)**2/R**2)**(-3/2) + (N*mu_0*I0)/(2*R) * (1 + (x + a/2)**2/R**2)**(-3/2)


def main():
    filnavn= 'kort_spole.csv'
    data =np.loadtxt(filnavn, delimiter=',')
    xe =data[:, 0]-x0   #posisjon,sentrertrundtx0
    Be =data[:, 1]      #m˚aledata

    #BeregnB-feltet
    xb =np.linspace(xe[0],xe[-1], 100)  #fleredatapunkter
    Bb1 = Helmholtzspoler(xb, R*2)*1e4       #beregnetB-felt(Gauss)
    Bb2 = Helmholtzspoler(xb, R)*1e4       #beregnetB-felt(Gauss)
    Bb3 = Helmholtzspoler(xb, R/2)*1e4       #beregnetB-felt(Gauss)

    #Plotresultatene
    plt.plot(xb,Bb1, label='Beregnet 1')
    plt.plot(xb,Bb2, label='Beregnet 2')
    plt.plot(xb,Bb3, label='Beregnet 3')
    plt.plot(xe,Be, '.',label='M˚aledata')
    plt.xlabel('Avstandfra senterav spolen(m)')
    plt.ylabel('Magnetfelt(Gauss)')
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    main()