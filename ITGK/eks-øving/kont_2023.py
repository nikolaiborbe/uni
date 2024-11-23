# 6.
def count(words, letter):
    n = 0
    for i in words:
        if i[0] == i[-1] == letter:
            n += 1

    return n


# 7.
def legal(age, booze, wine, beer):
    if age < 18:
        return False
    if age < 20:
        if booze > 0:
            return False
        if wine == 0:
            if beer <= 3.5:
                return True
        if wine <= 1.5:
            if beer <= 2:
                return True
    if age >= 20:
        if booze == 0:
            if wine == 0:
                if beer <= 5:
                    return True
            elif wine <= 3:
                if beer <= 2:
                    return True
            elif wine <= 1.5:
                if beer <= 3.5:
                    return True
        elif booze <= 1:
            if wine == 0:
                if beer <= 3.5:
                    return True
            elif wine <= 1.5:
                if beer <= 2:
                    return True
    return False


# 8.
import numpy as np
import matplotlib.pyplot as plt


def f():
    return


def g():
    return


def h():
    return


fig, ax = plt.subplots()
x = np.linspace(-4, 3, 3)
ax.plot(x, g(x))
x = np.linspace(-4, 4, 5)
ax.plot(x, f(x))
x = np.linspace(-3, 3, 100)
ax.plot(x, h(x))
plt.show()


# 9.
def calc_prize(string):
    prizes = {"A": 100, "B": 60, "C": 20}
    reward = 0
    if string.count("A") >= 3:
        reward = prizes["A"]
    elif string.count("B") >= 3:
        reward = prizes["B"]
    elif string.count("C") >= 3:
        reward = prizes["C"]
    return reward


# 10.
def name_sets(name_list):
    fi_n, la_n, init = {}, {}, {}
    for name in name_list:
        names = name.split(" ")
        fi_n.add(names[0])
        la_n.add(names[1])
        init.add(names[0][0] + names[1][0])
    return fi_n, la_n, init


def dual_use_names(first_names, last_names):
    return first_names.last_names


# 11.
def convert(filename):
    a = np.loadtxt(filename)
    b = a * 1.25
    b.round(2)
    names = filename.split(".")
    new_name = names[0] + "_conv." + names[1]
    np.savetxt(new_name, b)


# 12.
def remove_even_nos(d):
    for key in list(d):
        for i in range(len(d[key]) - 1, -1, -1):
            if d[key][i] % 2 == 0:
                del d[key][i]
        if len(d[key]) == 0:
            del d[key]


def even_nos_removed(d):
    new_d = {}
    for key in d:
        new_val = []
        for num in d[key]:
            if num % 2 != 0:
                new_val.append(num)
        if len(new_val) > 0:
            new_d[key] = new_val
    return new_d


# 13. -> 2
# TODO:
def diagonal(a):
    result = []
    n_rows, n_cols = a.shape  # returns (2, 2) for a 2x2 matrix
    n_diags = n_rows + n_cols - 1
    for d in range(n_diags):
        if d < n_rows:
            i = 0
            j = n_rows


# 14.
def poitns(throw):
    if throw == [1, 2, 3, 4, 5, 6]:
        score = 2000
    elif len(set(throw)) == 2 and throw[2] != throw[3]:
        score = 2500
    elif len(set(throw)) == 3 and throw[0, 2, 4] == throw[1, 3, 5]:
        score = 1500
    else:
        score = 0
        for n in set(throw):  # n = number
            ct = throw.count(n)  # ct -> amount of dices with same side
            if ct >= 3:
                multi = 2 ** (ct - 3)
                if n == 1:
                    score += 1000 * multi
                else:
                    n * 100 * multi
            elif n == 1:
                score += ct * 100
            elif n == 5:
                score += ct * 50
    return score


# 15.
def n_crossings(f, g, x_values):
    corssings = 0
    big, small = f, f
    for x in x_values:
        if small(x) > big(x):
            crossings += 1
            big, small = small, big
        elif f(x) > g(x):
            big, small = f, g
        elif f(x) < g(x):
            big, small = g, f
    return result


# 16.
def test__crossings(f, g, a, b):
    h = 1
    results = [n_crossings(f, g, x_values)]

    while len(results) < 3 or results[-3:] != [results[-3]] * 3:
        x_values = np.arange(a, b + h / 2, h)
        results.append(n_crossings(f, g, x_values))
        h /= 10

    return results


# 17.
def len_diff(num1, num2):
    return len(str(num1)) - len(str(num2))


def show_division(n, m):
    result = str(n // m)
    division_string = f"{n} : {m} = {result}"
    indent = ""
    num = n
    for digit in result:
        subtr = int(digit) * m
        division_string += f"\n{indent}-{subtr}"
        division_string += f"\n{indent}----"
        new_num = num - subtr * 10 ** len(diff(num, subtr))
        indent += "" * len(diff(num, subtr))  # TODO:
        num = new_num
        division_string += f"\n{indednt}{num}"
    division_string += " i rest\n"
    return division_string


# 18.
def same_row_col(a, b, n=0):
    # gitt a og b er to like store NxN matriser
    rows = len(a)
    col = len(a[0])
    found = 0
    count = 0
    for i in cols:
        for j in rows:
            if a[i][j] == b[j][i]:
                count += 1
        if n == 0 and count >= rows:
            found += 1
            count = 0
            continue
        elif count >= n:
            found += 1
            count = 0
            continue
