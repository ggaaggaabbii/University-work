nums = [2, 3, 5, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607]

def get_result(n):
	nb = 0
	for i in range (12, -1, -1):
		nb = pow(2, nums[i] - 1) * (pow(2, nums[i]) - 1)
		if nb < n:
			return nb
	return 0

print("this algorithm will determine the largest perfect number smaller than a given number n")
n = int(input("assign a value to n: "))
n = get_result(n)
if n == 0:
	print("there is no perfect number smaller than n")
else:
	print("the result is " + str(n))
