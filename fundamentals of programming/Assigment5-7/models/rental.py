from datetime import date

class rental:
	ID = 0
	def __init__(self, movieID, clientID, rentDate, dueDate, returnDate = 0):
		"""
		creates a rental object
		"""
		if dueDate < rentDate:
			raise ValueError("Due date must come after the rent date!")
		rental.ID += 1
		self._ID = rental.ID
		self._movieID = movieID
		self._clientID = clientID
		self._rentDate = rentDate
		self._dueDate = dueDate
		self._returnDate = returnDate

	def __str__(self):
		s = "\t"
		s += "ID: "
		s += str(self._ID)
		s += " The client "
		s += str(self._clientID)
		s += " rented the movie "
		s += str(self._movieID)
		s += "\n\t"
		s += "from date: "
		s += str(self._rentDate)
		s += " until "
		s += str(self._dueDate)
		if self._returnDate == 0:
			s += " and was not yet returned"
		else:
			s += " returned on "
			s += str(self._returnDate)
		s += "\n"
		return s

	def getID(self):
		"""
		outputs the id of a rental
		"""
		return self._ID

	def getMovieID(self):
		"""
		outputs the id of a the rented movie
		"""
		return self._movieID

	def getClientID(self):
		"""
		outpts the client
		"""
		return self._clientID

	def getRentDate(self):
		"""
		outputs the rent date
		"""
		return self._rentDate
	
	def getDueDate(self):
		"""
		outputs the due date
		"""
		return self._dueDate

	def getReturnDate(self):
		"""
		outputs the return date
		"""
		return self._returnDate

	def updateReturnDate(self, Date):
		"""
		updates the return date of a rental
		"""
		self._returnDate = Date

	def update(self, other):
		self.updateReturnDate(0)

	def resetIDCounter():
		rental.ID = 0
	
	def setIDCounter(value):
		rental.ID = value
