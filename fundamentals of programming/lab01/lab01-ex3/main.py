def	gcd(a, b):
	if b == 0:
		return a
	return gcd(b, a%b)
a = int(input("give a number: "))
b = int(input("give the other number: "))
print("the gcd is: " + str(gcd(a, b)))
