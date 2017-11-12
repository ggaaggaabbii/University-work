def validateAdd(listOfParams):
	"""
	check if the add function has 3 params
	"""
	if listOfParams == "":
		return False
	for params in listOfParams:
		if len(params) != 3:
			return False
	"""
	check if the 3 params are numbers
	"""
	for params in listOfParams:
		if validateNumber(str(params[0])) == False or validateNumber(str(params[1])) == False or validateNumber(str(params[2])) == False:
			return False
	"""
	check if the params are in range 0, 10
	"""
	for params in listOfParams:
		if params[0] < 0 or params[0] > 10 or params[1] < 0 or params[1] > 10 or params[2] < 0 or params[2] > 10:
			return False	
	return True	

def validateInsert(listOfParams):
	"""
	insert must have 5 params(including the parameter "at" which is part of the function
	"""
	if listOfParams == "":
		return False
	for params in listOfParams:
		if len(params) != 5:	
			return False
		"""
		check if the first 3 params are numbers
		"""
		if validateNumber(str(params[0])) == False or validateNumber(str(params[1])) == False or validateNumber(str(params[2])) == False:
			return False
		"""
		check if the last parameter(the position) is a number
		"""
		if validateNumber(str(params[4])) == False:
			return False
		"""
		check if the params are in the correct range of values
		"""
		if params[0] < 0 or params[0] > 10 or params[1] < 0 or params[1] > 10 or params[2] < 0 or params[2] > 10:
			return False
		if params[3] != "at":
			return False
		if params[4] < 0:
			return False
	return True

def validateRemove(listOfParams):
	"""
	check if the remove function is called for a single position
	"""
	if listOfParams == "":
		return False
	for params in listOfParams:
		if len(params) == 1:
			if validateNumber(str(params[0])) == False or params[0] < 0:
				return False
			"""
			check if the remove is called for a range 
			"""
		else:
			if len(params) == 3:
				if params[1] != "to":
					return False
				"""
				check if the 2 positions are numbers
				"""
				if validateNumber(str(params[0])) == False or params[0] < 0:
					return False
				if validateNumber(str(params[2])) == False or params[2] < 0:
					return False
				"""
				check if the positions are in the correct order
				"""
				if params[2] < params[0]:
					return False
			else:
				if len(params) != 2:
					if params[0] != "<" or params[0] != "=" or params[0] != ">":
						return False
					if validateNumber(str(params[1])) == False or params[1] < 0 or params[1] > 10:
						return False
	return True

def validateNumber(x):
	"""
	checks if a string is composed with only digits
	"""
	for i in range(0, len(x)):
		if x[i] < "0" or x[i] > "9":
			return False
	return True

def validateList(listOfParams):
	"""
	check if the list function is called with no params
	"""
	if listOfParams == "":
		return True
	if len(listOfParams) != 1:
		return False
	for params in listOfParams:
		"""
		check if the list is called to show the sorted list
		"""
		if len(params) == 1 and params[0] == "sorted":
			return True
		"""
		checks if the filter function is called correctly
		"""
		if len(params) != 2:
			return False
		if validateNumber(str(params[1])) == False or params[1] < 0 or params[1] > 10:
			return False
		if len(params) == 2 and (params[0] == "<" or params[0] == "=" or params[0] == ">"):
			return True
	return False

def validateExit(params):
	"""
	check if the exit function is called correctly
	"""
	if params == "":
		return True
	return False

def validateReplace(listOfParams):
	"""
	check if the number of params for replace function is correct
	"""
	if listOfParams == "":
		return False
	for params in listOfParams:
		if len(params) != 4:
			return False
		"""
		checks if the position and the value that will change are numbers
		"""
		if validateNumber(str(params[0])) == False or validateNumber(str(params[3])) == False:
			return False
		"""
		check if beside the params the function is called correctly
		"""
		if params[1] != "P1" and params[1] != "P2" and params[1] != "P3":
			return False
		if params[2] != "with":
			return False
	return True

def validateAvg_Min(listOfParams):
	if listOfParams == "":
		return False
	for params in listOfParams:
		"""
		check if its the right number of params
		"""
		if len(params) != 3:
			return False
		"""
		check if the the middle param is "to"
		"""
		if params[1] != "to":
			return False
		"""
		check if the 2 params are valid positive numbers
		"""
		if validateNumber(str(params[0])) == False or params[0] < 0:
			return False
		if validateNumber(str(params[2])) == False or params[2] < 0:
			return False
		if params[0] > params[2]:
			return False
	return True

def validateTop(listOfParams):
	"""
	check the number of params
	"""
	if len(listOfParams) != 1:
		return False
	for params in listOfParams:
		if len(params) == 1:
			if validateNumber(str(params[0])) == False:
				return False
		else:
			if len(params) != 2:
				return False
			if validateNumber(str(params[0])) == False:
				return False
			if params[1] != "P1" and params[1] != "P2" and params[1] != "P3":
				return False
	return True

def validateUndo(params):
	if params == "":
		return True
	return False

def validateCommand(cmd, params):
	"""
	determines whether a command is valid or not
	input - the command name and the the list of params
	output - True if the cammand is valid or False if not
	"""
	if cmd == "help" and params == "":
		return True
	if cmd == "add":
		return validateAdd(params)
	if cmd == "insert":
		return validateInsert(params)
	if cmd == "remove":
		return validateRemove(params)
	if cmd == "list":
		return validateList(params)
	if cmd == "exit":
		return validateExit(params)
	if cmd == "replace":
		return validateReplace(params)
	if cmd == "avg" or cmd == "min":
		return validateAvg_Min(params)
	if cmd == "top":
		return validateTop(params)
	if cmd == "undo":	
		return validateUndo(params)
	return False


