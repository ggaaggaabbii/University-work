import argparse
import random

alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ']
values = {}

parser = argparse.ArgumentParser(description='Simple tool used to encrypt/decrypt text')
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
parser.add_argument("-g",
	action='store_true',
	help="Generate a new key. If this parameter is present no other parameter is taken into acount",
	)
parser.add_argument("-k",
	metavar="--Key",
	type=str,
	help="The decryption/encryption key (Should be specified as value1;value2;value3;...;value n. The given key should be a valid permutation)"
	)

def is_valid_permutation(A):
	return min(A) == 1 and max(A) == len(A) == len(set(A))

def generate_key():
	length = random.randint(3, 10)
	numbers = [(x + 1) for x in range(length)]
	random.shuffle(numbers)
	s = ""
	for i in numbers:
		s += str(i) + ";"
	return s[:len(s) - 1]

def validate_input(text, action, key):
	for x in text:
		if x not in alphabet:
			print("Invalid text")
			return False

	allowed_actions = ['encrypt', 'decrypt']
	if action not in allowed_actions:
		print("Unkown action")
		return False

	numbers = key.split(";")
	for i in range(len(numbers)):
		try:
			numbers[i] = int(numbers[i])
		except:
			print("Invalid key")
			return False
	return is_valid_permutation(numbers)

def parse_key(key):
	numbers = key.split(";")
	for i in range(len(numbers)):
		numbers[i] = int(numbers[i])
	return numbers

def inverse_permutation(key):
	newKey = [0 for x in range(len(key))]
	for i in range(len(key)):
		newKey[key[i] - 1] = i + 1
	return newKey

def encrypt(text, key):
	newKey = parse_key(key)
	tmpText = text
	resultText = ""

	# add empty spaces to the end of the text to get a length multiple of the key length
	while (len(tmpText) // len(newKey) * len(newKey) != len(tmpText)):
		tmpText += " "

	# for each block, shuffle the elements acording to the key
	for i in range(len(tmpText) // len(newKey)):
		for j in range(len(newKey)):
			resultText += tmpText[i * len(newKey) + newKey[j] - 1]

	return resultText

def decrypt(text, key):
	newKey = inverse_permutation(parse_key(key))
	tmpText = text
	resultText = ""

	# add empty spaces to the end of the text to get a length multiple of the key length
	while (len(tmpText) // len(newKey) * len(newKey) != len(tmpText)):
		tmpText += " "

	# for each block, shuffle the elements acording to the key
	for i in range(len(tmpText) // len(newKey)):
		for j in range(len(newKey)):
			resultText += tmpText[i * len(newKey) + newKey[j] - 1]

	return resultText

def print_output(args):
	if args.g:
		print(generate_key())
		return
	if None == args.t:
		print("Missing mandatory parameter text")
		return
	if None == args.a:
		print("Missing mandatory parameter action")
		return
	if None == args.k:
		print("Missing mandatory parameter key")
		return
	if not validate_input(args.t, args.a, args.k):
		return

	if args.a == "encrypt":
		print(encrypt(args.t, args.k))
		return
	if args.a == "decrypt":
		print(decrypt(args.t, args.k))
		return

	return "Something went wrong"

if __name__ == '__main__':
	args = parser.parse_args()
	print_output(args)