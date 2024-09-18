import numpy as np
import matplotlib.pyplot as plt

"""
Oppgave:
- Lag to lister x_int = [1,2,3,4,5] og y_int = [1,2,3,4,5] som korresponderer til fem punkter i x-y-planet og lagre disse på en oversiktelig måte i ei .csv-fil ved bruk av `np.savetxt()`. Husk å gi navn på .csv-fila.

- Hent ut x- og y-listene fra fila ved bruk av `np.loadtxt()`.

- lag en kopi av y_int-dataene du leste fra .csv-fila, og manipuler elementene i denne lista slik at du får en ny liste, y, som inneholder kuben av alle elementene i y_int.

- Plot deretter både y_int og y som en funksjon av x_int med matplotlib i samme figur. 

- Gi de to funskjonene legend labels 'Data fra .csv' og 'Manipulert data'. 
"""

x_int, y_int = [1, 2, 3, 4, 5], [1, 2, 3, 4, 5]
data = np.column_stack((x_int, y_int))

np.savetxt("my_file.csv", data, delimiter=",", header="x_int, y_int")

load_data = np.loadtxt("my_file.csv", delimiter=",")
y_copy = load_data[:,1]
y = y_copy**2

plt.figure(1)
plt.plot(x_int, y, "r", label="Manipulert data")
plt.plot(x_int, y_copy, "o", label="Data fra .csv")
plt.xlabel("x-verdier")
plt.ylabel("y-verdier")
plt.legend()
plt.show()