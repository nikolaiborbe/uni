import numpy as np
import matplotlib.pyplot as plt
from oppg1 import sinc


def n_slit(D, x, lam, y, l, N):
    b = (np.pi * D * x) / (lam * y)
    d = (np.pi * l * x) / (lam * y)
    single_slit = sinc(b) ** 2
    multi_slit = np.where(d == 0, 1, (np.sin(N * d) / (N * np.sin(d))) ** 2)
    return single_slit * multi_slit


def opg2():
    """I'm assuming the question meant to say y instead of x as distance between slit and screen."""
    D = 2e-6  # m
    lam = 532e-9  # m
    y = 1  # m
    l = 4e-6  # m
    N = 3  # number of slits

    x = np.linspace(-1, 1, 1000)
    I = n_slit(D, x, lam, y, l, N)

    axes[0].plot(x, I)
    axes[0].set_xlabel("Position (m)")
    axes[0].set_ylabel("Normalized Intensity")

def opg2a():
    D = 2e-6  # m
    lam = 532e-9  # m
    y = 1  # m
    l = 4e-6  # m
    N = 3  # number of slits

    for i in np.linspace(l/2, 1.5*l, 3):
        x = np.linspace(-1, 1, 1000)
        I = n_slit(D, x, lam, y, i, N)
        axes[1].plot(x, I, label=f"l={i*1e6:.0f} um")

    axes[1].set_xlabel("Position (m)")
    axes[1].set_ylabel("Normalized Intensity")
    axes[1].legend()

if __name__ == "__main__":
    fig, axes = plt.subplots(2, 1)  # 1 rows, 2 columns

    opg2()
    opg2a()
    plt.show()
