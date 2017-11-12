def printMenu():
	print("0. Exit")
	print("1. Read a list of numbers")
	print("2. Show the list of numbers")
	print("3. Print the longest sequence in which all consecutive number pairs have the greatest common divisor 1")
	print("4. Print the longest sequence in which all consecutive numbers have at least 2 common digits")
	print("5. Print the longest sequence in which all numbers are prime numbers")
	print("6. Print the longest mountain sequence")

def gcd(a, b):
	"""
	a function that determines the gcd of 2 numbers
	input: 2 numbers a and b
	output: the gcd of a and b
	"""
	while b:
		a, b = b, a % b
	return a

def showSequence(List, pos1, pos2):
	print(List[pos1:pos2])

def isPrime(n):
	d = 3
	if n < 2:
		return False
	if int(n % 2) == 0 and n != 2:
		return False
	while d * d <= n:
		if int(n % d) == 0:
			return False
		d += 2
	return True

def checkProperty(List, prop):
	"""
	a function which determines the longest sequence with a given property
	input: List - the list of integer numbers and prop - the property function by which the sequence will be determined
	output: prints the sequence if there is one or prints an according message
	"""
	lSeq = 0
	iPos = 0
	fPos = 0
	ciPos = 0
	cfPos = 0
	clSeq = 1
	for i in range(0, len(List) - 1):
		if prop(List[i], List[i + 1]) == 1:
			clSeq += 1
			cfPos = i + 1
		else:
			clSeq = 1
			ciPos = i + 1
		if clSeq > lSeq:
			lSeq = clSeq
			iPos = ciPos
			fPos = cfPos
	if lSeq > 1:
		showSequence(List, iPos, fPos + 1)
	else:
		print("there is no such sequence")

def getPrimesequence(List):
	seq = 0
	ipos = 0
	cseq = 0
	for i in range(0, len(List)):
		if isPrime(List[i]):
			cseq += 1
		else:
			cseq = 0
		if cseq > seq:
			seq = cseq
			ipos = i - seq + 1
	if seq > 0:
		showSequence(List, ipos, ipos + seq)
	else:
		print("There are no prime numbers")

def getMountainseq(List):
	i = 0
	seq = 0
	cseq = 0
	ipos = 0
	while i < len(List) - 1:
		ok1 = False
		ok2 = False
		while i < len(List) - 1 and List[i] < List[i + 1]:
			cseq += 1
			i += 1
			ok1 = True
		while i < len(List) - 1 and List[i] > List[i + 1]:
			cseq += 1
			i += 1
			ok2 = True
		if (i == len(List) - 1 or List[i] < List[i - 1]) and ok1:
			cseq += 1
			ok2 = True
		if cseq > seq and ok1 and ok2:
			seq = cseq
			ipos = i - seq + 1
		if i < len(List) - 1 and List[i] == List[i + 1]:
			i += 1 
		cseq = 0
	if seq > 0:
		showSequence(List, ipos, ipos + seq)
	else:
		print("There is no mountain sequence")

def checkCommondigits(x, y):
	"""
	a function which determines if 2 numbers have at least 2 common digits
	input: 2 numbets x and y
	output: true if they respect the property or false otherwise
	"""
	v = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	w = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	comDig = 0
	while x:
		v[int(x % 10)] = 1
		x //= 10
	while y:
		w[int(y % 10)] = 1
		y //= 10
	for i in range(0, 10):
		if v[i] == 1 and w[i] == 1:
			comDig += 1
	if comDig >= 2:
		return 1
	return 0

def readList(List):
	print("Give a list of integers")
	List = [int(x) for x in input().split()]
	return List

def showList(List):
	print(List)

def start():
	List = []
	while True:
		printMenu()
		a = input()
		if a == "0":
			break
		elif a == "1":
			List = readList(List)
		elif a == "2":
			showList(List)
		elif a == "3":
			checkProperty(List, gcd)
		elif a == "4":
			checkProperty(List, checkCommondigits)
		elif a == "5":
			getPrimesequence(List)
		elif a == "6":
			getMountainseq(List)
		else:
			print("Error")

start()
