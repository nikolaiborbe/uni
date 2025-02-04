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

def get_data(file_path):
    data =np.loadtxt(file_path, delimiter=',', encoding="utf-8-sig",)
    x =data[:, 0]-x0   #posisjon,sentrertrundtx0
    y =data[:, 1]      #m˚aledata
    return x, y

def main():
    x1, y1 = get_data("data/helmholtzspoler/2R.csv")
    x1, y1 = get_data("data/helmholtzspoler/R_2.csv")
    x1, y1 = get_data("data/helmholtzspoler/R.csv")

    #BeregnB-feltet
    xb =np.linspace(x1[0],x1[-1], 100)  #fleredatapunkter
    Bb1 = Helmholtzspoler(xb, R*2)*1e4       #beregnetB-felt(Gauss)
    Bb2 = Helmholtzspoler(xb, R)*1e4       #beregnetB-felt(Gauss)
    Bb3 = Helmholtzspoler(xb, R/2)*1e4       #beregnetB-felt(Gauss)

    #Plotresultatene
    plt.plot(xb,Bb1, label='Beregnet 1')
    plt.plot(xb,Bb2, label='Beregnet 2')
    plt.plot(xb,Bb3, label='Beregnet 3')
    plt.plot(x1,y1, '.',label='M˚aledata')
    plt.xlabel('Avstandfra senterav spolen(m)')
    plt.ylabel('Magnetfelt(Gauss)')
    plt.legend()
    plt.show()
    
if __name__ == "__main__":
    main()