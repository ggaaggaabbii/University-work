def get_next_fibo(n, a, b):
	if a > n:
		return a;
	return get_next_fibo(n, b, a + b)

print("this algorithm will determine the smallest number from the Fibonacci sequence larger than a given number n")
n = int(input("assign a value to n: "))
print("the result is: " + str(get_next_fibo(n, 0, 1)))
