def palindrome(n):
	nb = 0
	while n:
		nb = nb * 10 + n % 10
		n /= 10
	return nb

print("this algorithm will determine a number's palindrome")
n = int(input("give a number: "))
print("it's palindrome is " + str(palindrome(n)))
