import numpy as np
import matplotlib.pyplot as plt
import csv

with open("data.csv", mode="r") as file:
    reader = csv.reader(file, delimiter=";")
    data   = [row for row in reader]
    
print(data)
genders     = [sublist[0] for sublist in data]
fag_info    = [sublist[2] for sublist in data]
itgk_info   = [sublist[3] for sublist in data]
hours_info  = [float(sublist[4]) for sublist in data]

tot_j   = genders.count("f")
tot_g   = genders.count("m")
tot_bi  = genders.count("bi")
antall_fag  = fag_info.count("True")
antall_itgk = itgk_info.count("True")
avg_hours   = sum(hours_info) / len(hours_info)

def plot_gender():
    labels = ["Jenter", "Gutter", "Bi"]
    values = [tot_j, tot_g, tot_bi]
    
    plt.pie(values, labels=labels)
    plt.axis("equal")
    plt.legend()
    plt.show()


def main_plt():
    cat = ["Menn", "Kvinner", "Ikke-binære", "Fag", "ITGK"]
    values = [tot_g, tot_j, tot_bi, antall_fag, antall_itgk]
    plt.bar(cat, values)
    plt.ylabel("Antall")
    plt.show()

main_plt()
    
