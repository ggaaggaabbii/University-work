from copy import deepcopy

def addScore(sList, score, position):
	"""
	adds a score to the list
	input - the list, the score(P1,P2,P3) and the position to where it should be added
	output - True if the adding was successful or False if the position is not accesible
	"""
	if position > len(sList) + 1:
		return False
	elif position == len(sList) + 1:
		sList.append(score)
	else:
		sList.insert(position - 1, score)
	return True

def removeScore(sList, startPos, endPos):
	"""
	removes a set of elements from the list
	input - the list, the starting position, the ending position
	output - True if the elements were deleted from the list or False if there was any problem
	"""
	if startPos < 1 or endPos > len(sList):
		return False
	for i in range(startPos - 1, endPos):
		sList.remove(sList[startPos - 1])
	return True

def averageScore(score):
	"""
	calculates the average score obtained by a person
	input - a score (P1/P2/P3)
	output - the average of P1, P2, P3
	"""
	return (score[0] + score[1] + score[2]) / 3

def showScores(sList):
	"""
	shows the entire list of scores
	"""
	if len(sList) == 0:
		print ("List is empty")
		return
	for i in sList:
		print (i)

def listSorted(sList):
	"""
	shows the list sorted by the avrage of the scores obtained
	input - the list
	output - -
	"""
	s = sorted(sList, key = averageScore, reverse = True)
	return s

def filterScores(sList, sign, value):
	"""
	shows the scores filtered by a given value
	input - the list, the sign (>,<,=), the value - integer
	output - -
	"""
	s = []
	ok = False
	if sign == "=":
		for i in sList:
			if averageScore(i) == value:
				s.append(i)
				ok = True
	if sign == "<":
		for i in sList:
			if averageScore(i) < value:
				s.append(i)
				ok = True
	if sign == ">":
		for i in sList:
			if averageScore(i) > value:
				s.append(i)
				ok = True
	if ok == False:
		return []
	return s

def replaceScore(sList, score, position, problem):
	"""
	replaces the score at a given position with a new one
	input - the list, a score, a position, P1/P2/P3 according to the problem
	output - True if the elem was replaced or False for any problem
	"""
	if position > len(sList) or position < 1:
		return False
	if problem == "P1":
		sList[position - 1][0] = score
	if problem == "P2":
		sList[position - 1][1] = score
	if problem == "P3":
		sList[position - 1][2] = score
	return True

def getMin(sList, startPos, endPos):
	"""
	computes the minimun average from a given range
	input - the list, the starting position and the last position
	output - the minimum average from the range or -1 if there is any error
	"""
	if startPos < 1 or endPos > len(sList):
		return -1
	Min = averageScore(sList[startPos - 1])
	for i in range(startPos, endPos):
		Min = min(Min, averageScore(sList[i]))
	return Min

def getAvg(sList, startPos, endPos):
	"""
	computes the average from a given range
	input - the list, the starting position and the last position
	output - the average on the average score from the range or -1 if there is any error
	"""
	if startPos < 1 or endPos > len(sList):
		return -1
	Sum = 0
	for i in range (startPos - 1, endPos):
		Sum += averageScore(sList[i])
	return Sum / (endPos - startPos + 1)

def getTop(sList, scoresToShow):
	"""
	computes first scoresToShow scores in the top
	input - the list and the number of scores to be displayed
	output - the list of scores or the empty set if there is a problem
	"""
	if scoresToShow > len(sList):
		return []
	s = sorted(sList, key = averageScore, reverse = True)
	return s[:scoresToShow]

def getTopByProblem(sList, scoresToShow, problem):
	"""
	computes the first scoresToShow scores obtained at a given problem
	input - sList, scoresToShow and the problem
	output - the list of scores or the empty set if there is a problem
	"""
	if scoresToShow > len(sList):
		return []
	if problem == "P1":
		index = 0
	if problem == "P2":
		index = 1
	if problem == "P3":
		index = 2
	s = sorted(sList, key = lambda x : x[index], reverse = True)
	return s[:scoresToShow]

def removeByFilter(sList, sign, value):
	"""
	removes from the list the scores filtered by the sign and the value
	input - the list, the sign and the value by which the list will be filtered
	output - 1 if at least 1 elem was removed, 0 if no elem was deleted, -1 for any error
	"""
	ok = False
	if sList == []:
		return -1
	i = 0
	if sign == "=":
		while i < len(sList):
			if averageScore(sList[i]) == value:
				sList.remove(sList[i])
				ok = True
				i -= 1
			i += 1
	elif sign == "<":
		while i < len(sList):
			if averageScore(sList[i]) < value:
				sList.remove(sList[i])
				ok = True
				i -= 1
			i += 1
	else:
		while i < len(sList):
			if averageScore(sList[i]) > value:
				sList.remove(sList[i])
				ok = True
				i -= 1
			i += 1
	if ok:
		return 1
	return 0
				

def undo(undoList):
	"""
	performes the undo operation on the list
	input - the list and the undo list which containes the list of lists before operations were performed on them
	output - the list before the last performed opetation
	"""
	if len(undoList) <= 1:
		s = []
	else:
		s = deepcopy(undoList[len(undoList) - 1])
		undoList.pop()
	return s

