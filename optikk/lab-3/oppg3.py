import numpy as np
import matplotlib.pyplot as plt
from oppg1 import sinc


def n_slit(D, x, lam, y, l, N):
    b = (np.pi * D * x) / (lam * y)
    single_slit = sinc(b) ** 2

    d = (np.pi * l * x) / (lam * y)
    multi_slit = np.where(d == 0, 1, (np.sin(N * d) / (N * np.sin(d))) ** 2)
    return single_slit * multi_slit


def opg3():
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


def opg3a():
    D = 2e-6  # m
    lam = 532e-9  # m
    y = 1  # m
    l = 4e-6  # m
    N = 3  # number of slits

    for n in range(1, 2 * N):
        x = np.linspace(-1, 1, 1000)
        I = n_slit(D, x, lam, y, l, n)
        axes[1].plot(x, I, label=f"N={n}")

    axes[1].set_xlabel("Position (m)")
    axes[1].set_ylabel("Normalized Intensity")
    axes[1].legend()


if __name__ == "__main__":
    fig, axes = plt.subplots(2, 1)  # 1 rows, 2 columns

    opg3()
    opg3a()
    plt.show()
