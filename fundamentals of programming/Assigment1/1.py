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

print("this algorithm will generate the first prime number greater than a given number n")

n = int(input("assing a value to n: "))

while check_prime(n + 1) == False:
	n += 1
print("the result is: " + str(n + 1))
