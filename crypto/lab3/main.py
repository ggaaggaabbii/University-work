import argparse

alphabet_values = {}
letter_for_value = {}

parser = argparse.ArgumentParser(description='Simple tool used to encrypt/' +
	'decrypt text')
parser.add_argument("-t",
	metavar="--Text",
	type=str,
	help="Original message",
	required=True
	)
parser.add_argument("-p",
	type=int,
	help="Bob's value",
	required=True
	)
parser.add_argument("-r",
	type=int,
	help="Alice's value",
	required=True
	)
parser.add_argument("-n",
	type=int,
	help="Modulus",
	required=True
	)
parser.add_argument("-b",
	type=int,
	help="base",
	required=True
	)

base = 0
ka = 0
kb = 0
MOD = 0

def squaring_modular_exponentiation_modulo(x, power, mod):
	result = 1

	while power > 0:
		if power % 2 == 1:
			result = (result * x) % mod
		power //= 2
		x *= x
		x %= mod

	return result

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

def encrypt(message, kb, r, mod):
	encrypted_message = []

	kakb = squaring_modular_exponentiation_modulo(kb, r, mod)

	for i in message:
		val = alphabet_values[i]
		encrypted_val = val * kakb % mod
		encrypted_message.append(encrypted_val)
		
	return encrypted_message

def decrypt(message, ka, p, mod):
	decrypted_message = ""

	kakb = squaring_modular_exponentiation_modulo(ka, p, mod)

	for i in message:
		decrypted_val = i * modular_inverse(kakb, mod) % mod
		decrypted_message += letter_for_value[decrypted_val]
		
	return decrypted_message

def print_output(args):
	global MOD, ka, kb, base
	MOD = args.n
	base = args.b
	ka = squaring_modular_exponentiation_modulo(base, args.r, MOD)
	kb = squaring_modular_exponentiation_modulo(base, args.p, MOD)
	print(ka, kb)

	encrypted = encrypt(args.t, kb, args.r, MOD)
	print(encrypted)
	print(decrypt(encrypted, ka, args.p, MOD))

if __name__ == '__main__':
	args = parser.parse_args()
	for i in range(26):
		alphabet_values[chr(ord('a') + i)] = i + 1
		letter_for_value[i + 1] = chr(ord('a') + i)
	alphabet_values[' '] = 0
	letter_for_value[0] = ' '
	print_output(args)