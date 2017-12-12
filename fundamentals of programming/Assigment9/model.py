class MyList:
	def __init__(self):
		self._list = {}
		self._index = 0
	
	def keys(self):
		return self._list.keys()
	
	def __setitem__(self, key, value):
		self._list[key] = value

	def __eq__(self, Dict):
		return self._list == Dict

	def __delitem__(self, key):
		del self._list[key]

	def __getitem__(self, key):
		return self._list[key]

	def __next__(self):
		try:
			Item = self._list[list(self._list)[self._index]]
		except IndexError:
			self._index = 0
			raise StopIteration()
		self._index += 1
		return Item

	def __iter__(self):
		return self


def sift(List, position, length, cmpFunction):
	"""
	lowers the position of a node in the tree until it is in a valid spot
	input: the list(heap), the position of the node in the tree the total length of the heap, the compare function
	"""
	node = position
	if 2 * position <= length and cmpFunction(List[node], List[2 * position]):
		node = 2 * position
	if 2 * position + 1 <= length and cmpFunction(List[node], List[2 * position + 1]):
		node = 2 * position + 1
	if node != position:
		List[node], List[position] = List[position], List[node]
		sift(List, node, length, cmpFunction)
	

def perlocate(List, position, length, cmpFunction):
	"""
	raises the position of a node until it is in a valid spot in the tree
	input: the list(heap), the position of the node in the tree, the total length of the list, the compare function
	"""
	while position > 1 and cmpFunction(List[position], List[position // 2]):
		List[position], List[position // 2] = List[position // 2], List[position]
		position //= 2

def buildHeap(List, cmpFunction):
	"""
	builds a heap from a list using a compare function
	input: the initial list, the compare function
	"""
	n = len(List)
	List.append(List[n - 1])
	for i in range(n, -1, -1):
		List[i] = List[i - 1]
	List[0] = 0
	for i in range(n // 2, 0, -1):
		sift(List, i, n, cmpFunction)

def defaultCmp(a, b):
	"""
	by default the heap will be a maxheap
	"""
	return a < b

def sort(List, cmpFunction = None):
	"""
	sorts a list using the heap sort algorithm
	input: the list, the compare function
	"""
	if List == []:
		return List
	if cmpFunction == None:
		cmpFunction = defaultCmp
	buildHeap(List, cmpFunction)
	n = len(List) - 1
	while n >= 2:
		List[1], List[n] = List[n], List[1]
		n -= 1
		sift(List, 1, n, cmpFunction)
	for i in range(len(List) - 1):
		List[i] = List[i + 1]
	List.pop()


def Filter(List, filterFunction = None):
	"""
	filters a list using a filter function
	input: the list, the filter function
	"""
	if filterFunction == None:
		return List
	newList = []
	for i in List:
		if filterFunction(i):
			newList.append(i)
	return newList
