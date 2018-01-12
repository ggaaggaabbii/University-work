def recursiveBacktracking(totalNumber):
	recursiveBack(0, 0, totalNumber, [])

def recursiveBack(leftParentheses, rightParentheses, totalNumber, solution):
	"""
	at each step we check whether we have to many of each type of parentheses
	if not and their sum is equal to the total number of parentheses, 
	it means we reached a solution
	then we recursively call the funtion again by adding on the current position whether an 
	open parentheses or a closed one
	"""
	if leftParentheses > totalNumber // 2:
		return
	if rightParentheses > totalNumber // 2:
		return
	if leftParentheses + rightParentheses == totalNumber:
		printSolution(solution)
		return
	recursiveBack(leftParentheses + 1, rightParentheses, totalNumber, solution + [0])
	if leftParentheses > rightParentheses:
		recursiveBack(leftParentheses, rightParentheses + 1, totalNumber, solution + [1])

def sol(List, length, totalNumber):
	"""
	checks if the current state can lead to a solution:
							-checks if the open parentheses are before the closed ones
							-checks if neither of them are more than half of the total number
	"""
	leftParentheses = 0
	rightParentheses = 0
	for i in range(length):
		if List[i] == 0:
			leftParentheses += 1
		if List[i] == 1:
			rightParentheses += 1
		if rightParentheses > leftParentheses:
			return False
	if leftParentheses > totalNumber // 2:
		return False
	if rightParentheses > totalNumber // 2:
		return False
	return True

def foundSol(List, length):
	"""
	checks whether the current configuration is valid by checking 
	if the number of open parentheses is equal to the number of close parentheses
	"""
	leftParentheses = 0
	rightParentheses = 0
	for i in range(length):
		if List[i] == 0:
			leftParentheses += 1
		if List[i] == 1:
			rightParentheses += 1

	return leftParentheses == rightParentheses

def iterativeBacktracking(totalNumber):
	"""
	at each step we try to put a value different larger than the previous one on each position
	if the formed configuration is valid we continue until 
	the last step when we check if the solution is a valid one
	we stop when the step goes below 0 beacause we used all the posible options for the 
	first position, therefor there is no way of getting to a valid solution
	"""
	solution = [-1 for x in range(totalNumber)]
	last = [0 for x in range(totalNumber)] #the last value assigned on each position
	step = 0
	while step != -1:
		if step == totalNumber:
			if foundSol(solution, totalNumber):
				printSolution(solution)
			step -= 1
			solution[step] = -1
		else:
			ok = True
			for i in range(last[step], 2):
				last[step] = i + 1
				solution[step] = i
				if sol(solution, step, totalNumber):
					ok = False
					step += 1
					break
			if ok == True:
				last[step] = 0
				step -= 1
				solution[step] = -1


def printSolution(List):
	"""
	transforms the list in a string with the coresponding characters
	"""
	string = ""
	for i in List:
		if i == 0:
			string += "("
		else:
			string += ")"
	print(string)


number = 10
print("Recursive: ")
recursiveBacktracking(number)
print("Iterative: ")
iterativeBacktracking(number)
