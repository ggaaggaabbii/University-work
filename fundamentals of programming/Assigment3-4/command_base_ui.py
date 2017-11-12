import list_module
import data_validation_module
from copy import deepcopy
import call_command as call
import test_module as t

def printHelp():
	"""
	prints the help menu
	"""
	print("Valid commands:")
	print("\t add <P1 score> <P2 score> <P3 score>")
	print("\t insert <P1 score> <P2 score> <P3 score> at <position>")
	print("\t remove <position>")
	print("\t remove <start position> to <end position>")
	print("\t remove [< / = / >] <score>")
	print("\t replace <position> <P1 / P2 / P3> with <new score>")
	print("\t list")
	print("\t list sorted")
	print("\t list [< / = / >] <score>")
	print("\t avg <start position> to <end position>")
	print("\t min <start position> to <end position>")
	print("\t top <number>")
	print("\t top <number> <P1 / P2 / P3>")
	print("\t undo")
	print("\t help")
	print("\t exit")

def readCommand():
	"""
	reads from the UI the current command
	input - -
	output - the command and the params of the command
	"""
	command = input("command: ")
	if command.find(" ") == -1:
		cmd = command
		listOfParams = ""
	else:
		cmd = command[0:command.find(" ")]
		listOfParams = command[command.find(" "):]
		listOfParams = listOfParams.split(",")	
		for i in range (0, len(listOfParams)):
			listOfParams[i] = str(listOfParams[i])
			listOfParams[i] = listOfParams[i].split()
			for j in range(0, len(listOfParams[i])):
				listOfParams[i][j] = listOfParams[i][j].strip()
				if data_validation_module.validateNumber(listOfParams[i][j]):
					listOfParams[i][j] = int(listOfParams[i][j])
	return (cmd,listOfParams)

def start():
	sList = []
	t.test_init(sList)
	undoList = [[]]
	while True:
		command = readCommand()
		cmd = command[0]
		listOfParams = command[1]
		if len(listOfParams) == 1:
			params = listOfParams[0][:]
		elif listOfParams == "":
			params = ""
		if data_validation_module.validateCommand(cmd, listOfParams):
			if cmd == "add":
				call.callAddFunction(sList, listOfParams, undoList)
			elif cmd == "insert":
				call.callInsertFunction(sList, listOfParams, undoList)
			elif cmd == "list":
				call.callListFunction(sList, params)
			elif cmd == "exit":
				break
			elif cmd == "remove":
				call.callRemoveFunction(sList, listOfParams, undoList)
			elif cmd == "replace":
				call.callReplaceFunction(sList, listOfParams, undoList)
			elif cmd == "help":
				printHelp()
			elif cmd == "avg":
				call.callAvgFunction(sList, listOfParams)
			elif cmd == "min":
				call.callMinFunction(sList, listOfParams)
			elif cmd == "undo":
				s = deepcopy(call.callUndoFunction(undoList))
				if s != []:
					sList = deepcopy(s)
			elif cmd == "top":
				call.callTopFunction(sList, params)
			else:
				print("Error")
		else:
			print("Error")

