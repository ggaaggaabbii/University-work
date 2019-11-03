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
	help="The decryption/encryption key (Should be specified as a=value1;b=value2;c=value3;...;z=value26;space=value27)"
	)

def generate_key():
	s = ""
	v = [x for x in range(0, len(alphabet))]
	random.shuffle(v)
	for i in range(0, len(alphabet)):
		s += alphabet[i] + "=" + str(v[i]) + ";"

	return s[:len(s) - 1].replace(" ", "space")


def validate_key(key):
	print(key)
	v = key.split(';')
	if len(v) != len(alphabet):
		return False
	for i in range(0, len(alphabet)):
		
	return True


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
	if not validate_key(args.k):
		print("Invalid key")
		return
	 

if __name__ == '__main__':
	args = parser.parse_args()
	print_output(args)