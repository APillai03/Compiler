MOD = 998244353

def mod_exp(base, exp, mod):
    result = 1
    while exp > 0:
        if exp % 2 == 1:
            result = (result * base) % mod
        base = (base * base) % mod
        exp //= 2
    return result

def beautiful_grids(m, n):
    if n==1:
        return 0
    exponent = m * n - m - n + 1
    return mod_exp(2, exponent, MOD)

# Sample Inputs
print(beautiful_grids(4, 1))  # Output: 0
print(beautiful_grids(5, 7))  # Output: 0
print(beautiful_grids(3, 3))  # Example square grid case
