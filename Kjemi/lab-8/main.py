import csv
import matplotlib.pyplot as plt


def plot_potential_per_volume(volume, potential):
    v0 = volume[0]
    vol = [v - v0 for v in volume]
    plt.plot(vol, potential, marker="+", linestyle="-")
    plt.grid()
    plt.ylabel("$E$ [mV]")
    plt.xlabel("$V$ [ml]")
    plt.show()


with open("data.csv") as f:
    reader = csv.DictReader(f)
    volume = []
    potential = []
    for row in reader:
        volume.append(float(row["volume"]))
        potential.append(float(row["potential"]))

plot_potential_per_volume(volume, potential)
