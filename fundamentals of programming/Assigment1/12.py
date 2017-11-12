def digits_check(n, m):
	v = []
	w = []	
	for i in range(0, 10):
		v.append(0)
		w.append(0)
	while n:
		v[n % 10] = 1
		n /= 10
	while m:
		w[m % 10] = 1
		m /= 10
	for i in range(0, 10):
		if v[i] != w[i]:
			return False
	return True

print("this algorithm will determine whether or not the same digits were used to write to numbers")
n = int(input("first number: "))
m = int(input("second number: "))
if digits_check(n, m):
	print("the numbers are wirtten with the same digits")
else:
	print("the numbers have different digits")

