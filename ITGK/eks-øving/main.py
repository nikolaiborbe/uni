import numpy as np

def longest_increase(f, x_values):
    result = ()
    current_start = None

    for i in range(1, len(x_values)):
        if f(x_values[i]) > f(x_values[i - 1]):
            if current_start is None:
                current_start = x_values[i - 1]
            elif result == ():
                if x_values[i] - current_start > result[1] - result[0]:
                    result = (current_start, x_values[i])
        else:
            if current_start is not None:
                if x_values[i - 1] - current_start > result[1] - result[0]:
                    result = (current_start, x_values[i - 1])
                current_start = None
    return result

print(longest_increase(np.sin, np.arange(-6.0,6.0,0.01)) )