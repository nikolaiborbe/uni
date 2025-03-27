import subprocess
import matplotlib.pyplot as plt
import numpy as np
from ink import print_ink
from dek import print_dek

def main():
    result = subprocess.run("clear", shell=True, capture_output=True, text=True)
    print(result.stdout)
    print_dek("data.csv")
    print("")
    print_ink("data.csv")

if __name__ == "__main__":
    main()

