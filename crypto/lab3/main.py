import argparse

alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ']
values = {}

parser = argparse.ArgumentParser(description='Simple tool used to encrypt/' +
	'decrypt text')
parser.add_argument("-t",
	metavar="--Text",
	type=str,
	help="Original message"
	)
parser.add_argument("-a",
	metavar="--Action",
	type=str,
	help="Action to be executed on the text (decrypt/encrypt)"
	)
parser.add_argument("-p",
	type=int,
	help="Bob's value")
parser.add_argument("-r",
	type=int,
	help="Alice's value")
parser.add_argument("-n",
	type=int,
	help="Modulus")
parser.add_argument("-b",
	type=int,
	help="base")

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

def encrypt(text):
	pass

def decrypt(text):
	pass

def print_output(args):
	global MOD, ka, kb, base
	MOD = args.n
	base = args.b
	ka = squaring_modular_exponentiation_modulo(base, args.r, MOD)
	kb = squaring_modular_exponentiation_modulo(base, args.p, MOD)

	if args.a == "encrypt":
		print(encrypt(args.t))
		return
	if args.a == "decrypt":
		print(decrypt(args.t))
		return

	return "Something went wrong"

if __name__ == '__main__':
	args = parser.parse_args()
	print_output(args)