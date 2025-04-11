import numpy as np
import matplotlib.pyplot as plt

# Definer funksjonen f(x) og dens deriverte f'(x)
def f(x):
    return x**2

def fprime(x):
    return 2*x

# Velg et startpunkt x_n og beregn y_n, stigning, og det neste punktet x_next
x_n = 1.5
y_n = f(x_n)
slope = fprime(x_n)

# Newtons metode: x_{n+1} = x_n - f(x_n)/f'(x_n)
x_next = x_n - y_n/slope

# Sett opp x-verdier for plotting
x_vals = np.linspace(-1, 2.5, 300)
y_vals = f(x_vals)

# Beregn tangentlinja: y = f'(x_n) * (x - x_n) + f(x_n)
tangent_vals = slope * (x_vals - x_n) + y_n

# Plott funksjonen, tangentlinja og de relevante punktene
plt.figure(figsize=(8, 6))
plt.plot(x_vals, y_vals, label=r'$f(x)=x^2$', color='blue')
plt.plot(x_vals, tangent_vals, '--', label='Tangent ved $x_n$', color='red')

# Marker punktet (x_n, f(x_n)) og x_{n+1} på x-aksen
plt.plot(x_n, y_n, 'ko', label=r'$(x_n, f(x_n))$')
plt.plot(x_next, 0, 'ro', label=r'$(x_{n+1}, 0)$')

# Tegn hjelpelinjer for x- og y-aksene
plt.axhline(0, color='black', linewidth=0.5)
plt.axvline(0, color='black', linewidth=0.5)

# Legg til en kort tekst som forteller antall Newton-iterasjoner (her 1 steg)
plt.text(x_n+0.05, y_n/2, f"Slope = {slope:.2f}", color='red', fontsize=10)

plt.xlabel('x')
plt.ylabel('f(x)')
plt.title("Ett Newton-steg for $f(x)=x^2$")
plt.grid(True)
plt.legend()
plt.show()
