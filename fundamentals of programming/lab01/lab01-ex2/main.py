def is_prime(n):
    if (n % 2 == 0 & n != 2):
        return 0
    d = 3
    while d * d <= n:
        if (n % d == 0):
            return 0
        d += 2
    if n == 1:
        return 0
    return 1


a = int(input("give a number: "))

if is_prime(a):
    print("the number is prime")
else:
    print("the number is not prime")
