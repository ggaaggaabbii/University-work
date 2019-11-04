import sys

sys.setrecursionlimit(1000000)

surname = "gote"
k = 2
l = 3

p = 73
q = 79
n = p * q # 5767
phi_n = (p - 1) * (q - 1) # 5616
e = 5 # encryption key

alphabet_values = {}
letter_for_value = {}

public_key = (n, e)
# private key is d = e^(-1) mod phi_n

def extended_euclidian_algorithm(a, b):
	if a == 0:
		return (b, 0, 1)
	g, x, y = extended_euclidian_algorithm(b % a, a)
	return (g, y - (b // a) * x, x)

def modular_inverse(a, n):
	g, x, _ = extended_euclidian_algorithm(a, n)
	if g == 1:
		return x % n
	return None

def squaring_exponentiation(x, power, mod):
	result = 1

	while power > 0:
		if power % 2 == 1:
			result = (result * x) % mod
		power //= 2
		x *= x
		x %= mod

	return result

def encrypt(message, public_key):
	n = public_key[0]
	e = public_key[1]

	encrypted_message = ""

	for i in range(len(message) // k):
		val = 0
		for j in range(k):
			val *= 27
			val += alphabet_values[message[i * k + j]]

		new_val = squaring_exponentiation(val, e, n)

		# take the corresponding letters
		first_letter = new_val // (27 ** 2)
		new_val -= first_letter * (27 ** 2)
		second_letter = new_val // 27
		new_val -= second_letter * 27
		third_letter = new_val

		encrypted_message += letter_for_value[first_letter]
		encrypted_message += letter_for_value[second_letter]
		encrypted_message += letter_for_value[third_letter]

	return encrypted_message

def decrypt(message, public_key):
	n = public_key[0]
	e = public_key[1]
	d = modular_inverse(e, phi_n)
	decrypted_message = ""

	for i in range(len(message) // l):
		val = 0
		for j in range(l):
			val *= 27
			val += alphabet_values[message[i * l + j]]

		new_val = squaring_exponentiation(val, d, n)

		# take the corresponding letters
		first_letter = new_val // 27
		new_val -= first_letter * 27
		second_letter = new_val

		decrypted_message += letter_for_value[first_letter]
		decrypted_message += letter_for_value[second_letter]

	return decrypted_message

def gcd(a, b):
	if b == 0:
		return a
	return gcd(b, a % b)

def check_key_validity(e, phi_n):
	return gcd(e, phi_n) == 1

if __name__ == "__main__":
	for i in range(26):
		alphabet_values[chr(ord('a') + i)] = i + 1
		letter_for_value[i + 1] = chr(ord('a') + i)
	alphabet_values[' '] = 0
	letter_for_value[0] = ' '

	if not check_key_validity(e, phi_n):
		print("Key is not valid")

	encrypted_message = encrypt(surname, public_key)
	decrypted_message = decrypt(encrypted_message, public_key)

	print(surname)
	print(encrypted_message)
	print(decrypted_message)
	