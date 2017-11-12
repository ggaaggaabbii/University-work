"""
manage rational numbers:
	-add numer
	-delete at index
	-sum between indices
	-multiple undo
"""
from copy import deepcopy
def gcd(a, b):
	if b == 0:
		return a
	return int(gcd(b, a % b))

def test_gcd():
	for i in range(1, 10):
		assert gcd(i, i + 1) == 1
	for i in range(1, 10):
		assert gcd(i, 2 * i) == i

def  addNumber(sList, n, m):
	if m == 0:
		return False
	Gcd = gcd(n, m)
	n /= Gcd
	m /= Gcd
	sList.append([int(n), int(m)])
	return True

def test_addNumber():
	sList = []
	for i in range(1, 10):
		assert addNumber(sList, i, i + 1) == True
	for i in range(1, 10):
		assert addNumber(sList, i, 0) == False

def deleteAtIndex(sList, index):
	if index < 1 or index > len(sList):
		return False
	sList.remove(sList[index - 1])
	return True

def test_deleteAtIndex():
	sList = []
	test_init(sList)
	for i in range(1, 7):
		assert deleteAtIndex(sList, 1) == True
	for i in range(1, 10):
		assert deleteAtIndex(sList, 0) == False

def sumBetweenIndeces(sList, startPos, endPos):
	if startPos < 1 or endPos > len(sList):
		return -1
	Sum = 0
	Lcm = sList[startPos - 1][1]
	for i in range(startPos - 1, endPos):
		Lcm = sList[i][1] * Lcm / gcd(sList[i][1], Lcm)
	for i in range(startPos - 1, endPos):
		Sum += sList[i][0] * Lcm / sList[i][1]
	Gcd = gcd(Sum, Lcm)
	Sum /= Gcd
	Lcm /= Gcd
	return (int(Sum), int(Lcm))

def test_sumBetweenIndeces():
	sList = []
	test_init(sList)
	for i in range(1, 10):
		assert sumBetweenIndeces(sList, i, i) == (sList[i - 1][0], sList[i - 1][1])

def test_init(sList):
	for i in range(1, 10):
		addNumber(sList, i, i + 1)

def undo(undoList, times):
	for i in range(0, times):
		s = deepcopy(undoList[len(undoList) - 1])
		undoList.pop()
	return s	

def printMenu():
	print("Menu:1 add, 2 delete, 3 sum, 4 undo 5 show 0 exit")

def start():
	sList = []
	test_init(sList)
	undoList = []
	while True:
		printMenu()
		command = input()
		if command == "1":
			numbers = input()
			numbers = numbers.split()
			if len(numbers) != 2:
				print("Error")
			else:
				undoList.append([])
				undoList[len(undoList) - 1] = deepcopy(sList)
				addNumber(sList, int(numbers[0]), int(numbers[1]))
		elif command == "2":
			index = int(input("at what index"))
			if index < 1 or index > len(sList):
				print("Error")
			else:
				undoList.append([])
				undoList[len(undoList) - 1] = deepcopy(sList)
				deleteAtIndex(sList, index)
		elif command == "0":
			break
		elif command == "3":
			numbers = input()
			numbers = numbers.split()
			if len(numbers) != 2:
				print("Error")
			else:
				print(sumBetweenIndeces(sList, int(numbers[0]), int(numbers[1])))
		elif command == "4":
			times = int(input("how many times "))
			if times > len(undoList):
				print("Error")
			sList = deepcopy(undo(undoList, times))
		elif command == "5":
			print(sList)
		else:
			print("Error")


test_gcd()
test_addNumber()
test_deleteAtIndex()
test_sumBetweenIndeces()
start()
