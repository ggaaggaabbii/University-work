class movie:

	allowedGenres = ['Drama', 'Thriller', 'Comedy', 'Romance', 'Action', 'Adventure', 'Sci-Fi', 'Horror']

	def __init__(self, ID = -1, title = -1, description = -1, genre = -1):
		"""
		creates a movie object
		"""
		self.check(ID, title, description, genre)
		self._ID = ID
		self._title = title
		self._description = description
		self._genre = genre
		
	def __str__(self):
		return "\tID:" + str(self._ID) + ". " + self._title + "\n" + "\tDescription: " + self._description + "\n" + "\tGenre: " + self._genre + "\n"

	def __eq__(self, other):
		return self.getID() == other.getID() and self.getTitle() == other.getTitle() and self.getDescription() == other.getDescription() and self.getGenre() == other.getGenre()

	def updateID(self, ID):
		self._ID = ID

	def updateTitle(self, title):
		"""
		updates the title of a movie
		"""
		self._title = title

	def updateDescription(self, description):
		"""
		updates the description of a movie
		"""
		self._description = description

	def updateGenre(self, genre):
		"""
		updates the genre of a movie
		"""
		if genre not in movie.allowedGenres:
			raise ValueError("Invalid Genre!")
		self._genre = genre
	
	def getID(self):
		"""
		outputs the id of a movie
		"""
		return self._ID

	def getTitle(self):
		"""
		outputs the title of a movie
		"""
		return self._title

	def getDescription(self):
		"""
		outputs the description of a movie
		"""
		return self._description

	def getGenre(self):
		"""
		outputs the genre of a movie
		"""
		return self._genre

	def check(self, ID = -1, title = -1, description = -1, genre = -1):
		"""
		checks if the movie is initialized correctly
		"""
		if ID == -1 or title == -1 or description == -1 or genre == -1:
			raise TypeError("Missing a parameter!")
		
		if genre not in movie.allowedGenres:
			raise TypeError("Unknown genre!")

	def getSearchStr(self):
		"""
		computes the string that will be used in the search function
		"""
		return str(self._ID) + " " + self._title + " " + self._description + " " + self._genre

	def update(self, other):
		"""
		performs the update of an element
		input: the new element
		"""
		self.updateTitle(other.getTitle())
		self.updateDescription(other.getDescription())
		self.updateGenre(other.getGenre())
