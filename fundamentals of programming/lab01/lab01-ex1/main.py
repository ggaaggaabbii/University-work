def sumab(a, b):
    return a + b


n = int(input("how many number will there be: "))
s = 0
for i in range(1, n + 1):
    a = int(input("give a number: "))
    s = sumab(s, a)
print(s)
