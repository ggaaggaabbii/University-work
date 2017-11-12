nums = [2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607]

def get_result(n):
	nb = 0
	for i in range (0, 13):
		nb = pow(2, nums[i] - 1) * (pow(2, nums[i]) - 1)
		if nb > n:
			return nb
	return 0

print("this algorithm will determine the smallest perfect number larger than a given number n")
n = int(input("assign a value to n: "))
print("the result is " + str(get_result(n)))
