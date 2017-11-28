class repo():
	
	def __init__(self):
		self._list = {}
	
	def getList(self):
		"""
		returns the entire list
		input: the current repo
		output: the list of elements
		"""
		return self._list

	def addElement(self, element):
		"""
		adds an element to the list
		input: the current repo and the element
		raise: error if the id of the element already exists in the list
		"""
		if element.getID() in self._list.keys():
			raise ValueError("ID already used!")
		self._list[element.getID()] = element

	def updateElement(self, ID, newElement):
		"""
		updates an element of the list
		input: the current repo, the id of the element and the element it will be replaced with
		raise: error if the id can not be found in the list
		"""
		if ID not in self._list.keys():
			raise ValueError("Invalid ID!")
		self._list[ID].update(newElement)

	def removeElement(self, ID):
		"""
		delets an element from the list
		input: the repo and the id 
		raise: error if the id is not in the list
		"""
		if ID not in self._list.keys():
			raise ValueError("Invalid ID!")
		del self._list[ID]
	
	def getByID(self, ID):
		"""
		returns an the element with a specific id
		input: the current repo and the id
		output: the element with the id
		raise: error if the id is not in the repo
		"""
		if ID not in self._list.keys():
			raise ValueError("Invalid ID")
		return self._list[ID]

	
