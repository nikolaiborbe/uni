import numpy as np
import matplotlib.pyplot as plt


def sinc(x):
    return np.where(x == 0, 1, np.sin(x) / x)


def fraunhofer(x, lam, D, y):
    b = np.pi * D * x / (lam * y)
    return sinc(b) ** 2


def opg1():
    lam = 532e-9  # m
    D = 2e-6  # m
    y = 1  # m

    x = np.linspace(-1, 1, 1000)  # m
    I = fraunhofer(x, lam, D, y)
    axes[0, 0].plot(x, I)
    axes[0, 0].set_xlabel("Position (m)")
    axes[0, 0].set_ylabel("Normalized Intensity")


def opg1a():
    lam = 532e-9  # m
    y = 1  # m
    D = 2e-6  # m

    for D in np.linspace(D / 2, 2 * D, 5):  # m
        x = np.linspace(-1, 1, 1000)  # m
        I = fraunhofer(x, lam, D, y)
        axes[0, 1].plot(x, I, label=f"$D={D*1e6:.0f} \\mu m$")
    axes[0, 1].legend()
    axes[0, 1].set_xlabel("Position (m)")
    axes[0, 1].set_ylabel("Normalized Intensity")


def opg1b():
    D = 2e-6  # m
    y = 1  # m
    lam = 532e-9  # m

    for lam in np.linspace(lam / 2, 2 * lam, 5):  # m
        x = np.linspace(-1, 1, 1000)  # m
        I = fraunhofer(x, lam, D, y)
        axes[1, 0].plot(x, I, label=f"$\\lambda={lam*1e9:.0f} nm$")
    axes[1, 0].legend()
    axes[1, 0].set_xlabel("Position (m)")
    axes[1, 0].set_ylabel("Normalized Intensity")

def opg1c():
    D = 25e-6  # m
    y = 0.32  # m
    lam = 532e-9  # m

    x = np.linspace(-0.1, 0.1, 1000)  # m
    I = fraunhofer(x, lam, D, y)
    axes[1, 1].plot(x, I)
    axes[1, 1].set_xlabel("Position (m)")
    axes[1, 1].set_ylabel("Normalized Intensity")
    axes[1, 1].set_title("D=25um, y=0.32m, $\\lambda=532$nm")
    axes[1, 1].legend()


if __name__ == "__main__":
    fig, axes = plt.subplots(2, 2)  # 2 rows, 2 columns

    opg1()
    opg1a()
    opg1b()
    opg1c()
    plt.show()
