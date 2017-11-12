def is_prime(n):
	if n < 2:
		return False
	if n % 2 == 0 and n != 2:
		return False
	d = 3
	while d * d <= n:
		if n % d == 0:
			return False
		d += 2
	return True

def solve(n):
	while is_prime(n + 1) != True or is_prime(n + 3) != True:
		n += 1
	print ("the twin prime numbers are: " + str(n + 1) + " and " + str(n + 3))

print ("this algorithm will determine the first pair of twin prime numbers larger than a given number n")
n = int(input("assign a value to n: "))
solve(n)
