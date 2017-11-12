def prime_factors(n):
	global currentstep
	d = 2
	ok = False
	aux = n
	while d <= aux / 2:
		if n % d == 0:
			while n % d == 0:
				n /= d
			for i in range(1, d + 1):
				currentstep += 1
				if currentstep == laststep:
					print("the n'th element is " + str(d))
					currentstep += 1
					return 1
			ok = True
		d += 1
	if ok:
		return 1
	return 0

def solve():
	global currentstep
	for i in range(1, laststep + 1):
		if prime_factors(i) == 0:
			currentstep += 1
			if currentstep == laststep:
				print("the n'th element is " + str(i))
				return

print("this algorithm will determine the n'th element from the sequence 1, 2, 3, 2, 2, 5 ... where any non-prime number is replaced with it's prime factors and any prime factor d is written d times")
laststep = int(input("assign a value to n: "))
currentstep = 0
solve()				
