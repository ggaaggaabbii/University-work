import model.airport as air

def addFlight(fList, flight):
	"""
	calls the same function, but from the airport module
	"""
	return air.addFlight(fList, flight)

def printFlights(fList):
	"""
	calls the same function but from the airport module
	"""
	air.printFlights(fList)

def deleteFlight(fList, code):
	"""
	calls the same function but from the airport module
	"""
	return air.deleteFlight(fList, code)

def listSorted(fList, depCity):
	return air.listSorted(fList, depCity)

def incrementDuration(fList, params):
	return air.incrementDuration(fList, params[0], params[1])
