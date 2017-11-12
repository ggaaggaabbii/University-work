def get_minimal(n):
	v = [0, 0, 0, 0, 0, 0, 0, 0, 0,0]
	nb = 0
	while n:
		v[n % 10] += 1
		n /= 10
	for i in range (1, 10):
		if v[i] != 0:
			v[i] -= 1
			nb = i
			break
	for i in range (0, 10):
		for j in range (0, v[i]):
			nb = nb * 10 + i
	return nb

print("this algorithm will determine the smallest number that can be built with n's digits")
n = int(input("assign a value to n: "))
print("the result is " + str(get_minimal(n)))
