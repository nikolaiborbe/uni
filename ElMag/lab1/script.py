with open("data/kort_spole.csv", "r") as file:
    lines = file.readlines()

with open("output.csv", "w") as file:
    file.writelines(lines[::2])  # Keep every other line (0, 2, 4, ...)

print("Every other line removed. Output saved in 'output.txt'.")
