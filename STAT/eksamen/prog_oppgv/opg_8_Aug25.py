from random import uniform

def simX(n: int) -> list[float]:
    out = []
    for _ in range(n):
        u = uniform(0,1)
        Y = (1-u)**(-1/3)
        out.append(Y)

    return out

print(simX(10))
