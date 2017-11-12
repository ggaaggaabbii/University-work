import list_module
import data_validation_module as valid
import call_command as call
from copy import deepcopy
import test_module as t

def printMenu():
	print("1. Add an element or multiple elements")
	print("2. Insert an element to a position")
	print("3. Show the list")
	print("4. Remove elements from the list")
	print("5. Replace elements")
	print("6. Average on a range")
	print("7. Minimum on a range")
	print("8. Get the top scores")
	print("9. Undo")
	print("0. Exit")
	
def printAddSubmenu():
	print("An element should have the following form: <P1_score P2_score P3_score> where all values are integers. You can add multiple elements if you split them by \",\"")

def printInsertSubmenu():
	print("An element should have the form: <P1 P2 P3> where all values are int. You should specify where the element will be added by \"at\" <position>. You can insert multiple elements if you split them by \",\"")

def printShowSubmenu():
	print("You can press ENTER to show the list. You can show the list sorted (sorted). You can show the list filtered ([<, =, >] <value>)")

def printRemoveSubmenu():
	print("You can remove by specifying the position (<position>), a range(<starting position> to <end position>), or by a filter([>, =, <] <value>). You can remove by more criterias if you split them by \",\"")

def printReplaceSubmenu():
	print("Specify: position(<position>) problem(<P1/P2/P3>) and the value(with <value>)")

def printAverageSumbenu():
	print("Specity the range(<start Position> to <end Position>)")

def printMinSubmenu():
	print("Specify the range(<start Position> to <end Position>)")

def printGetTopSubmenu():
	print("Specify how many candidates will be shown(<number>) and if you want to show the top at a problem, just pecify the problem(<P1 P2 P3>)")

def printSubmenu(c):
	if c == "1":
		printAddSubmenu()
	if c == "2":
		printInsertMenu()
	if c == "3":
		printShowSubmenu()
	if c == "4":
		printRemoveSubmenu()
	if c == "5":
		printReplaceSubmenu()
	if c == "6":
		printAverageSubmenu()
	if c == "7":
		printMinSubmenu()
	if c == "8":
		printGetTopSubmenu()

def readCommandParams():
	listOfParams = input()
	if listOfParams == "":
		return listOfParams
	listOfParams = listOfParams.split(",")
	for i in range(0, len(listOfParams)):
		listOfParams[i] = str(listOfParams[i])
		listOfParams[i] = listOfParams[i].split()
		for j in range(0, len(listOfParams[i])):
			listOfParams[i][j] = listOfParams[i][j].strip()
			if valid.validateNumber(listOfParams[i][j]):
				listOfParams[i][j] = int(listOfParams[i][j])
	return listOfParams

def start():
	sList = []
	t.test_init(sList)
	undoList = [[]]
	while True:
		printMenu()
		c = input()
		if c != "0" and c != "9":
			printSubmenu(c)
			listOfParams = readCommandParams()
			if len(listOfParams) == 1:
				params = listOfParams[0][:]
			elif listOfParams == "":
				params = ""
		if c == "1" and valid.validateAdd(listOfParams):
			call.callAddFunction(sList, listOfParams, undoList)
		elif c == "2" and valid.validateInsert(listOfParams):
			call.callInsertFunction(sList, listOfParams, undoList)
		elif c == "3" and valid.validateList(listOfParams):
			call.callListFunction(sList, params)
		elif c == "4" and valid.validateRemove(listOfParams):
			call.callRemoveFunction(sList, listOfParams, undoList)
		elif c == "5" and valid.validateReplace(listOfParams):
			call.callReplaceFunction(sList, listOfParams, undoList)
		elif c == "6" and valid.validateAvg_Min(listOfParams):
			call.callAvgFunction(sList, listOfParams)
		elif c == "7" and valid.validateAvg_Min(listOfParams):
			call.callMinFunction(sList, listOfParams)
		elif c == "8" and valid.validateTop(listOfParams):
			call.callTopFunction(sList, params)
		elif c == "9":
			s = deepcopy(call.callUndoFunction(undoList))
			if s != []:
				sList = deepcopy(s)
		elif c == "0":
			break
		else:
			print("Error")
			
