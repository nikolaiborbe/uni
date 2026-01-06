import numpy as np 


class Q1:
    n = 100000
    s = 0
    for _ in range(n):
        u = np.random.uniform(0,1)
        y = 2*np.sqrt(u)

        if y <= 0.4: 
            s += 1 

    print(s/n)
        

