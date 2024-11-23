# 6
def sum_except(numlist, n):
    g = 0
    for i in numlist:
        if i == n:
            g += 1
    for i in range(g):
        numlist.remove(numlist[i])
    return numlist


# 7
def ok_size(length, width, intl):
    if intl:
        if length >= 100 and length <= 110:
            if width >= 64 and width <= 75:
                return True
    else:
        if length >= 90 and length <= 120:
            if width >= 45 and width <= 90:
                return True
    return False


# 8
def a_and_b(A, B):
    result = A.intersection(B)
    return result


def a_butnot_b(A, B):
    result = A.difference(B)
    return result


def common_cars(car_geeks):
    result = car_geeks[0]
    for B in car_geeks[1:]:
        result = result.intersection(B)
    return result


def all_cars(car_geeks):
    result = set()
    for B in car_geeks:
        result = result.union(B)
    return result


# 9
def flip_values(L, m):
    for i in range(1, len(L), 2):
        for j in range(len(L[i])):
            L[i][j] = m - L[i][j]


def values_flipped(L, M):
    new_L = []
    for i in range(len(L)):
        if i % 2 == 0:
            new_L.append(L[i][:])
        else:
            new_L.append([m - x for x in L[i]])

    return new_L


# 10 TODO: check if this makes sense
import numpy as np


def change_file(filename):
    A = np.loadtxt(filename)
    A = np.abs(A)
    for i in range(len(A)):
        for j in range(len(A[i])):
            if abs(A[i, j]) >= 100:
                A[i, j] = -A[i, j]
    np.savetxt(filename, A)


# 11
def same_numbers_row_col(M, order):
    result = []
    for i in range(len(M)):
        for j in range(len(M[i])):
            if (
                list(M[i]) == list(M[i, j])
                and not order
                or sorted(list(M[i]) == sorted(list(M[i, j])))
            ):
                result.append([i, j])

    return result


# 12
import numpy as np
import matplotlib.pyplot as plt


def f(x):
    pass


def g(x):
    pass


def h(x):
    pass


fig, ax = plt.subplots()
x = np.linspace(-3, 4, 100)
ax.plot(x, g(x))
x = np.arange(-4, 5)
ax.plot(x, f(x))
x = np.linsapce(-3, 3, 100)
ax.plot(x, h(x))
plt.show()


# 13
def card_val(card):
    special = {"J": 11, "Q": 12, "K": 13, "A": 14}
    if card[1:] in special:
        return special[card[card[1:]]]
    else:
        return int(card[1:])


# 14
def straight(cards):
    numbers = []
    for c in cards:
        numbers.append(card_val(c))
    m = min(numbers)
    s = set(numbers)
    return s == set(range(m, m + 5)) or s == {2, 3, 4, 5, 14}


def flush(cards):
    kinds = []
    for c in cards:
        kinds.append(c[0])
    return len(set(kinds)) == 1


# 15
def strick_incr(f, x_values):
    result = True
    for i in range(len(x_values)):
        if f(x_values[i]) <= f(x_values[i - 1]):
            result = False
            break
    return result


# 16
def longest_incr(f, x_values):
    start = long_start = end = long_end = x_values[0]
    for i in range(1, len(x_values)):
        if f(x_values[i] > f(x_values[i - 1])):
            end = x_values[i]
            if end - start > long_end - long_start:
                long_start, long_end = start, end
        else:
            start = end = x_values[i]
    return (long_start, long_end)


# 17
import numpy as np


def export_fee(wt):
    wt_limits = np.array((10, 100, 500, 1000, 5000))
    fees = np.array((2000, 3000, 4000, 6000, 8000))

    wt_fees = np.zeros(len(fees))

    for i in range(len(wt_fees)):
        if wt > wt_limits[i]:
            wt_fees[i] = (wt - wt_limits[i])* fees[i]
            wt = wt - wt_limits[i]
    
    return np.sum(wt_fees)

#18 -> 7 pts
import numpy as np
A = np.array([[1.7, 1.4, 1.8, 2.2],
              [2.6, 3.8, 3.4, 3.8],
              [4.2, 4.6, 0.9, 5.5],
              [5.8, 6.2, 6.6, 7.3],
              [9.9, 7.8, 5.2, 8.6]])


def count_local_min(A):
    count += 1
    for i in range(len(A)):
        for j in range(len(A[i])):
            min_row = max(0, i-1)
            max_row = min(len(A)-1, i+1)
            min_col = max(0, j-1)
            max_col = min(len(A[i])-1, j+1)
            if A[i,j] == np.min(A[min_row:max_row+1, min_col:max_col+1]):
                count += 1
    return count