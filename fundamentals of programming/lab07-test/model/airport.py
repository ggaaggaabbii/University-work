def addFlight(fList, flight):
	"""
	adds a flight to the flights list
	input: the list, a flight
	output: true if the adding could be performed
	raise: error if the id of the flight is already in the list or the details of the flight do not meet the requirements
	"""
	if flight[0] in fList.keys():
		raise ValueError("The Flight code is invalid")
	if len(flight[0]) < 3 or len(flight[2]) < 3 or len(flight[3]) < 3 or flight[1] < 20:
		raise TypeError("Invalid Flight")
	fList[flight[0]] = flight
	return True

def deleteFlight(fList, code):
	"""
	removes a flight from the list
	input: the list, the code of the flight that is about to be removed
	output: true if the remove could be performed
	raise: error if the id of the flight could not be found in the list
	"""
	if code not in fList.keys():
		raise ValueError("Invalid code")
	del fList[code]
	return True

def listSorted(fList, depCity):
	"""
	returnes the list of flights with a given departure city sorted by their destination city
	"""
	sortedList = []
	for i in fList.keys():
		if fList[i][2] == depCity:
			sortedList.append(fList[i])
	if len(sortedList) == 0:
		raise ValueError("No flight starting from that city")
	"""
	print(sorted(sortedList, key = lambda x : x[3]))
	"""
	return sorted(sortedList, key = lambda x : x[3])

def incrementDuration(fList, depCity, duration):
	if duration < 10 or duration > 60:
		raise ValueError("Invalid duration")
	for i in fList.keys():
		if fList[i][2] == depCity:
			fList[i][1] += duration
	return True

def printFlights(fList):
	"""
	prints the list to the screen
	"""
	if len(fList.keys()) == 0:
		raise ValueError("The list is empty")
	for i in fList.keys():
		print(fList[i])
