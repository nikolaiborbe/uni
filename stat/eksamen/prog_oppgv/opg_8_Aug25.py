from numpy.random import uniform

def simX(n: int) -> list[float]:
    u = uniform(0, 1, size = n)
    x = (1-u)**(-1/3)
    return x


print(simX(100))
