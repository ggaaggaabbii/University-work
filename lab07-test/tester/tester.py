import model.airport as air

def testAddFlight():
	fList = testInit()
	assert air.addFlight(fList, ["32123", 40, "New York", "Chicago"]) == True
	try:
		air.addFlight(fList, ["0B3002", 42, "Bucuresti", "Amsterdam"])
		assert False
	except Exception:
		assert True
	try:
		air.addFlight(fList, ["32", 40, "Bucuresti", "Amsterdam"])
		assert False
	except Exception:
		assert True
	try:
		air.addFlight(fList, ["33232", 19, "Bucuresti", "Amsterdam"])
		assert False
	except Exception:
		assert True
	

def testDeleteFlight():
	fList = testInit()
	assert air.deleteFlight(fList, "0B3002") == True
	assert air.deleteFlight(fList, "0E321") == True
	try:
		air.deleteFlight(fList, "0000")
		assert False
	except Exception:
		assert True

def testListSorted():
	fList = testInit()
	sortedList =  [['0E321', 60, 'Los Angeles', 'Bucuresti'],['0B3002', 45, 'Los Angeles', 'Las, Vegas']]
	assert air.listSorted(fList, "Los Angeles") == sortedList

def testIncrementDuration():
	fList = testInit()
	fList2 = testInit()
	fList2['0E321'][1] += 15
	fList2['0B3002'][1] += 15
	air.incrementDuration(fList)
	assert fList == fList2

def test_all():
	testAddFlight()
	testDeleteFlight()
	testListSorted()
	testIncrementDuration()

def testInit():
	return {"0B3002" : ["0B3002", 45, "Los Angeles", "Las Vegas"], "0E321": ["0E321", 60, "Los Angeles", "Bucuresti"], "31F24" : ["31F24", 35, "Brasov", "Arges"]}
