# Find all bases with respect to which a given number n is pseudoprime
# n pseudoprime to b if gcd(b, n) = 1 and b^(n - 1) % n = 1
import argparse

d = 'Find all bases with respect to which a given '
d += 'number n is pseudoprime'

parser = argparse.ArgumentParser(description=d)
parser.add_argument(
	"-n",
	dest='n',
	type=int,
	required=True,
	help="Input number")

def gcd(a, b):
	if b == 0:
		return a
	return gcd(b, a % b)

def squaring_modular_exponentiation_modulo(x, power, mod):
	result = 1

	while power > 0:
		if power % 2 == 1:
			result = (result * x) % mod
		power //= 2
		x *= x
		x %= mod

	return result

def get_pseudoprime_bases(n):
	if n < 1:
		return []

	bases = []

	for b in range(2, n):
		# if gcd(b, n) != 1:
		# 	continue
		if squaring_modular_exponentiation_modulo(b, n - 1, n) != 1:
			continue
		bases.append(b)

	return bases

if __name__ == "__main__":
	args = parser.parse_args()
	print(get_pseudoprime_bases(args.n))