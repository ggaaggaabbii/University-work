def solve(n):
	i = 2
	rez = 1
	while i * i <= n:
		if i * i == n:
			rez *= i
		elif n % i == 0:
			rez *= i
			rez *= n / i
		i += 1
	return rez

print ("this algorithm will determine the product of a number's proper factors")
n = int(input("give a number: "))
n = solve(n)
if n == 1:
	print ("the number has no proper factors")
else:
	print("the product of it's proper factors is " + str(n))
