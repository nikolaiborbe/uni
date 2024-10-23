import time
import timeit
import numpy as np
import random

###############
# Oppgave a.
###############
np_list = np.arange(0, 10_000_001)
py_list = [
    i
    for i in range(10_000_000)
]

def np_ar():
    out = []
    for i in np_list:
        if i % 7 == 0:
            out.append(i)

def py_ar():
    out = []
    for i in py_list:
        if i % 7 == 0:
            out.append(i)

start_time = time.perf_counter()
np_ar()
end_time = time.perf_counter()
elapsed_time = (end_time - start_time) * 1_000_000
print(f"np_ar took {elapsed_time:.3f} µs to run.")

start_time = time.perf_counter()
py_ar()
end_time = time.perf_counter()
elapsed_time = (end_time - start_time) * 1_000_000  
print(f"py_ar took {elapsed_time:.3f} µs to run.")


###############
# Oppgave b.
###############
setup_code = """
import numpy as np
import random
py_list = random.sample(range(10_000_001), 10_000_000)
np_array = np.array(py_list)
"""

sorted_test = "sorted(py_list)"
sort_test = "py_list.sort()"
np_sort_test = "np.sort(np_array)"

sorted_time = timeit.timeit(stmt=sorted_test, setup=setup_code, number=1)
sort_time = timeit.timeit(stmt=sort_test, setup=setup_code, number=1)
np_sort_time = timeit.timeit(stmt=np_sort_test, setup=setup_code, number=1)

print(f"sorted() took {sorted_time:.3f} seconds")
print(f"list.sort() took {sort_time:.3f} seconds")
print(f"np.sort() took {np_sort_time:.3f} seconds")
