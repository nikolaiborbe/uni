import numpy as np
A = np.array(
    [
        [1., 1.4, 1.8, 2.2],
        [2.6, 3.8, 3.4, 3.8],
        [4.2, 4.6, 0.9, 5.4],
        [5.8, 6.2, 6.6, 7.3],
        [9.9, 7.8, 5.2, 8.6],
    ]
)

def sum_near_whole(A):
    rows = len(A)
    cols = len(A[0])
    tot = 0
    for i in range(len(A)):
        for j in range(len(A[i])):
            item_above = max(0, i-1)
            item_below = min(rows-1, i+1)
            item_left = max(0, j-1)
            item_right = min(cols-1, j+1)

            if A[i,j] == int(A[i, j]):
                try:
                    tot += A[item_above, j]
                except IndexError:
                    pass
                try:
                    tot += A[item_below, j]
                except IndexError:
                    pass
                try:
                    tot += A[i, item_right]
                except IndexError:
                    pass
                try:
                    tot += A[i, item_left]
                except IndexError:
                    pass
    return tot

print(sum_near_whole(A))