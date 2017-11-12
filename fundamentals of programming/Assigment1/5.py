def check_prime(n):
	if n <= 1:
		return False
	if n % 2 == 0 and n != 2:
		return False
	d = 3
	while d * d <= n:
		if n % d == 0:
			return False
		d += 2
	return True

def get_result(n):
	for i in range(n, 1, -1):
		if check_prime(i):
			return i
	return 0

print("this algorithm will determine the largest prime number smaller than a given number n")
n = int(input("assign a value to n: "))
n = get_result(n - 1)
if n != 0:
	print("the result is " + str(n))
else:
	print("there is no prime number smaller than n")
