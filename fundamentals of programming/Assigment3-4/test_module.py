import list_module as t

def test_removeByFilter():
	sList = []
	assert t.removeByFilter(sList, "=", 1) == -1
	test_init(sList)
	assert t.removeByFilter(sList, "<", 1) == 0
	assert t.removeByFilter(sList, "=", 4) == 1
	assert t.removeByFilter(sList, ">", 7) == 1

def test_getTopByProblem():
	sList = []
	assert t.getTopByProblem(sList, 1, "P1") == []
	test_init(sList)
	assert t.getTopByProblem(sList, 2, "P1") == [[10, 7, 9], [10, 5, 4]]
	assert t.getTopByProblem(sList, 1, "P2") == [[7, 9, 7]]
	assert t.getTopByProblem(sList, 1, "P3") == [[9, 8, 10]]

def test_getTop():
	sList = []
	sortedList = [[9, 8, 10], [10, 7, 9], [7, 9, 7], [8, 8, 7], [7, 6, 8], [4, 6, 10], [10, 5, 4], [2, 8, 3], [5, 3, 4], [2, 4, 6]]
	assert t.getTop(sList, 1) == []
	test_init(sList)
	for i in range(1, len(sList)):
		assert t.getTop(sList, i) == sortedList[:i], i
	
def test_getAvg():
	sList = []
	for i in range (1, 10):
		assert t.getAvg(sList, i, i) == -1, i
	test_init(sList)
	for i in range(1, len(sList) + 1):
		assert t.getAvg(sList, i, i) == t.averageScore(sList[i - 1]), i

def test_getMin():
	sList = []
	for i in range(1, 10):
		assert t.getMin(sList, i, i) == -1, i
	test_init(sList)
	for i in range(1, len(sList) + 1):
		assert t.getMin(sList, i, i) == t.averageScore(sList[i - 1]), i

def test_undo():
	sList = []
	test_init(sList)
	pass

def test_addScore():
	sList = []
	test_init(sList)
	for i in range(1, 10):
		assert t.addScore(sList, (i, i - 1, i + 1), len(sList)) == True, i
	for i in range(1, 10):
		assert t.addScore(sList, (i, i - 1, i + 1), i) == True, i
	for i in range(1, 10):
		assert t.addScore(sList, (i, i - 1, i + 1), len(sList) + i + 1) == False, i 

def test_removeScore():
	sList = []
	test_init(sList)
	for i in range(1, 5):
		assert t.removeScore(sList, i, i) == True, i
	test_init(sList)
	for i in range(1, 5):
		assert t.removeScore(sList, 1, 2) == True, i
	test_init(sList)
	for i in range(1, 10):
		assert t.removeScore(sList, len(sList) + 1, len(sList) + 1) == False, i

def test_listSorted():
	sList = []
	test_init(sList)
	sortedList = [[9, 8, 10], [10, 7, 9], [7, 9, 7], [8, 8, 7], [7, 6, 8], [4, 6, 10], [10, 5, 4], [2, 8, 3], [5, 3, 4], [2, 4, 6]]
	assert t.listSorted(sList) ==  sortedList

def test_replaceScore():
	sList = []
	test_init(sList)
	problem = ["P1", "P2", "P3"]
	for i in range(1, 10):
		assert t.replaceScore(sList, i, i, problem[i % 3]) == True, i
	for i in range(1, 10):
		assert t.replaceScore(sList, i, len(sList) + i, problem[i % 3]) == False, i
	
def test_init(sList):
	"""
	adds elems to the initial list
	input - the list
	output - -
	"""
	sList.append([7, 6, 8])#avg = 7
	sList.append([10, 7, 9])#avg = 8.66
	sList.append([5, 3, 4])#avg = 4
	sList.append([2, 8, 3])#avg = 4.33
	sList.append([9, 8, 10])#avg = 9
	sList.append([4, 6, 10])#avg = 6.66
	sList.append([10, 5, 4])#avg = 6.33
	sList.append([7, 9, 7])#avg = 7.66
	sList.append([2, 4, 6])#avg = 4
	sList.append([8, 8, 7])#avg = 7.66

def test_averageScore():
	for i in range(1, 100):
		assert t.averageScore((i - 1, i, i + 1)) == i, i

def test_all():
	test_addScore()
	test_removeScore()
	test_averageScore()
	test_listSorted()
	test_replaceScore()
	test_getAvg()
	test_getMin()
	test_removeByFilter()
	test_getTop()
	test_getTopByProblem()
