import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

N =330 #[]antallviklinger
I0 =1.0 #[A]strøm
mu_0 =4.0*np.pi*1e-7 #[H/m] permeabilitetitomtrom
R =0.07 #[m]radius
x0 =0.400 #[m]sentrumavspolen

def anti_Helmholtzspoler(x, a):
    const = N*mu_0*I0/(2*R)
    return const * ((1+(x-a/2)**2/(R**2))**-(3/2) - (1+(x+a/2)**2/(R**2))**-(3/2))

def get_data(file_path):
    data =np.loadtxt(file_path, delimiter=',', encoding="utf-8-sig", skiprows=1)
    x =data[:, 0]-x0   #posisjon,sentrertrundtx0
    y =data[:, 1]      #m˚aledata
    return x, y

def main():
    x1, y1 = get_data("data/anti-helmholtzspoler/2R.csv")
    x2, y2 = get_data("data/anti-helmholtzspoler/R_2.csv")
    x3, y3 = get_data("data/anti-helmholtzspoler/R.csv")

    #BeregnB-feltet
    xb =np.linspace(-0.2, .2, 100)  #fleredatapunkter
    Bb1 = [anti_Helmholtzspoler(x, R*2)*1e4 for x in xb]      #beregnetB-felt(Gauss)
    Bb2 = [anti_Helmholtzspoler(x, R)*1e4 for x in xb]      #beregnetB-felt(Gauss)
    Bb3 = [anti_Helmholtzspoler(x, R/2)*1e4 for x in xb]      #beregnetB-felt(Gauss)

    #Plotresultatene
    plt.plot(xb-0.6,Bb1, label='Beregnet 1')
    plt.plot(xb-0.6,Bb2, label='Beregnet 1')
    plt.plot(xb-0.6,Bb3, label='Beregnet 1')
    plt.plot(x1,y1, '.',label='Måledata')
    plt.plot(x2,y2, '.',label='Måledata')
    plt.plot(x3,y3, '.',label='Måledata')
    plt.xlabel('Avstandfra senterav spolen(m)')
    plt.ylabel('Magnetfelt(Gauss)')
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    main()