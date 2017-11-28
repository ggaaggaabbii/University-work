class client:

	def __init__(self, ID = -1, name = -1):
		"""
		creates the client object
		input: the client's name
		output: raises an error if the name is incorect
		"""
		if self.checkName(ID, name):
			raise TypeError("Name must be a string!")
		self._ID = ID
		self._name = name
	
	def __str__(self):
		"""
		defines the way a client object is printed out
		"""
		return "\tID:" + str(self._ID) + ". " + self._name + "\n"

	def updateID(self, ID):
		"""
		updates the id of a client
		"""
		self._ID = ID

	def updateName(self, name):
		"""
		updates the name of the client
		"""
		self._name = name

	def getID(self):
		"""
		outputs the id of a client
		"""
		return self._ID

	def getName(self):
		"""
		outputs the name of a client
		"""
		return self._name

	def checkName(self, ID, name = -1):
		"""
		checks if the name is correct
		"""
		if name == -1:
			raise TypeError("Missing Name!")
		if ID == -1:
			raise TypeError("Missing ID!")
		for i in range(len(name)):
			if i == 0 or name[i - 1] == " ":
				if name[i] < 'A' or name[i] > 'Z':
					raise ValueError("Each part of the name must begin with capital letter")
			elif (name[i] < 'a' or name[i] > 'z') and name[i] != ' ':
				return True
		return False

	def getSearchStr(self):
		"""
		computes the string that will be used in the search function
		"""
		return str(self._ID) + " " + self._name

	def update(self, other):
		"""
		performs the update of an element
		input: the new element
		"""
		self.updateID(other.getID())
		self.updateName(other.getName())

