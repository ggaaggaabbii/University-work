v = []

def ciur(n):
	for i in range(0, n + 1):
		v.append(0)
	v[0] = 1
	v[1] = 1
	for i in range(2, n + 1):
		if v[i] == 0:
			j = i + i
			while j <= n:
				v[j] = 1
				j += i

def solve(n):
	ciur(n)
	for i in range (2, n / 2 + 1):
		if v[i] == 0 and v[n - i] == 0:
			print ("the number is the sum of " + str(i) + " and " + str(n - i))
			return
	print ("the number can not be written as a sum of 2 prime numbers") 

print("this algorithm will determine whether or not a number can be written as the sum of 2 prime numbers")
n = int(input("give a natural number: "))
solve(n)
