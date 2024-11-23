# 6
def sum_larger(numlist, n):
    tot = 0
    for i in numlist:
        if i > n:
            tot += i
    return tot


# 7
def car_type(n_pass, wt, person: bool):
    if person:
        if n_pass <= 8:
            return "M1"
        elif wt <= 5000:
            return "M2"
        else:
            return "M3"
    else:
        if wt <= 3500:
            return "N1"
        elif wt > 3500 and wt <= 12000:
            return "N2"
        else:
            return "N3"


# 8
def countries_either(m, m2):
    result = m.union(m2)
    return result


def contries_both(m, m2):
    result = m.intersection(m2)
    return result


def countries_covered(club_members):
    result = set()
    for m in club_memebers:
        result = result.union(m)


def countries_exclusive(m, blub_members):
    result = m
    for m2 in club_memebers:
        if m2 is not m:
            result = result.difference(m2)
    return result


# 9
def adjuct_list(L, length):
    for i in range(len(L)):
        if len(L[i]) < length:
            L[i] += [0] * (length - len(L[i]))
        else:
            del L[i][length:]


def lists_adjusted(L, length):
    new_L = []
    for lst in L:
        if len(lst) >= length:
            new_L.append(lst[:length])
        else:
            new_L.append(lst + [0] * (length - len(lst)))
    return new_L


# 10
import numpy as np


def edit_file(filename):
    A = np.loadtxt(filename)
    for i in range(len(A)):
        for j in range(len(A[i])):
            if abs(A[i, j]) > 50:
                A[i, j] = 100 - abs(A[i, j])
    np.savetxt(filename, A)


# 11
def equal_products_row_col(A, zero):
    result = []
    for i in range(len(A)):
        p = np.prod(A[i])
        for j in range(len(A[i])):
            if (zero or p != 0) and p == np.prod(A[:, j]):
                result.append([p, i, j])
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
x = np.linsapce(-4, 4, 100)
ax.plot(x, f(x))
x = np.arange(-3, 5, 0.75)
ax.plot(x, h(x))
x = np.linspace(-3, 3, 100)
ax.plot(x, g(x))
plt.show()

# 13
def card_no(card):
    if card[1] in "JQKA":
        return "1" + "JQKA".find(card[1])
    else:
        return int(card[1:])