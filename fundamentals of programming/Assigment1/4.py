def get_maximal(n):
	v = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	nb = 0
	while n:
		v[n % 10] += 1
		n /= 10
	for i in range (9, -1, -1):
		for j in range (0, v[i]):
			nb = nb * 10 + i
	return nb

print ("this algorithm will determine the largest possible number built with n's digits")
n = int(input("assign a value to n: "))
print (get_maximal(n))
