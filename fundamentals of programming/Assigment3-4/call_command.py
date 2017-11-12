import list_module
from copy import deepcopy

def callAddFunction(sList, listOfParams, undoList):
	"""
	performes the add command
	"""
	undoList.append([])
	undoList[len(undoList) - 1] = deepcopy(sList)
	for Params in listOfParams:
		if list_module.addScore(sList, Params, len(sList) + 1) == False:
			print ("Error")
			break

def callInsertFunction(sList, listOfParams, undoList):
	"""
	performes the insert command
	"""
	undoList.append([])
	undoList[len(undoList) - 1] = deepcopy(sList)
	for Params in listOfParams:
		if list_module.addScore(sList, [Params[0], Params[1], Params[2]], Params[4]) == False:
			print("Error")
			break

def callListFunction(sList, params):
	"""
	performes the list command
	"""
	if params == "":
		list_module.showScores(sList)
	elif params[0] == "sorted":
		List = list_module.listSorted(sList)
		if List == []:
			print("List is empty")
		else:
			for i in List:
				print(i)
	else:
		List = list_module.filterScores(sList, params[0], params[1])
		if List == []:
			print("No such elements")
		else:
			for i in List:
				print(i)

def callRemoveFunction(sList, listOfParams, undoList):
	"""
	performes the remove command
	"""
	undoList.append([])
	undoList[len(undoList) - 1] = deepcopy(sList)
	for Params in listOfParams:
		if len(Params) == 1:
			if list_module.removeScore(sList, Params[0], Params[0]) == False:
				print("Error")
				break
		else:
			if len(Params) == 3:
				if list_module.removeScore(sList, Params[0], Params[2]) == False:
					print("Error")
					break	
			else:
				remove = list_module.removeByFilter(sList, Params[0], Params[1])
				if remove == -1:
					print("Error")
				elif remove == 0:
					print("No element was removed")

def callReplaceFunction(sList, listOfParams, undoList):
	"""
	performes the replace command
	"""
	undoList.append([])
	undoList[len(undoList) - 1] = deepcopy(sList)
	for Params in listOfParams:
		if list_module.replaceScore(sList, Params[3], Params[0], Params[1]) == False:
			print("Error")
			break

def callAvgFunction(sList, listOfParams):
	"""
	performes the avg command
	"""
	for Params in listOfParams:
		avg = list_module.getAvg(sList, Params[0], Params[2])
		if avg == -1:
			print("Error")
			break
		else:
			print(avg)

def callMinFunction(sList, listOfParams):
	"""
	performes the min command
	"""
	for Params in listOfParams:
		Min = list_module.getMin(sList, Params[0], Params[2])
		if Min == -1:
			print("Error")
			break
		else:
			print(Min)

def callTopFunction(sList, params):
	"""
	performes the top command
	"""
	if len(params) == 1:
		s = list_module.getTop(sList, params[0])
		if s == []:
			print("Error")
		else:
			for i in s:
				print(i)
	else:
		s = list_module.getTopByProblem(sList, params[0], params[1])
		if s == []:
			print("Error")
		else:
			for i in s:
				print(i)

def callUndoFunction(undoList):
	s = deepcopy(list_module.undo(undoList))
	if s == []:
		print("You've reached the end")
	return s
