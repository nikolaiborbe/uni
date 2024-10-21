x0 = 0.38

def f(x):
    return 9 + (1/3)*sin(x)

def df(x):                  # The derivative f'
    return (1/3)*cos(x)

x, nit = newton(f, df, x0, tol=1.e-14, max_iter=30)  # Apply Newton
print('\n\nResult:\nx={}, number of iterations={}'.format(x, nit))


