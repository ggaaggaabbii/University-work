class Point:
	def __init__(self, x, y):
		"""
		initializes the point
		input: the x, y position
		"""
		self.x = x
		self.y = y

	def __eq__(self, other):
		"""
		checks if 2 points are equal
		"""
		return self.x == other.x and self.y == other.y

class Plane:
	def __init__(self, position, orientation, player):
		"""
		initializes the plane for a given position, orientation and a coresponding player
		input: a Point coreponding to the position of the head, the orientation and the player
		"""
		self._otherPositions = []
		if orientation == 'N':
			self._scalarX = 1
			self._scalarY = 0
		elif orientation == 'S':
			self._scalarX = -1
			self._scalarY = 0
		elif orientation == 'W':
			self._scalarX = 0
			self._scalarY = 1
		else:
			self._scalarX = 0
			self._scalarY = -1
		self.validatePlane(position, player)
		self._position = position
		self._orientation = orientation
		self._player = player
		if self._player == 'Ai':
			self._position.y += 10
		self.computeOtherPositions()

	def getPlayer(self):
		"""
		returns the player coresponding to the plane
		"""
		return self._player

	def getPosition(self):
		"""
		returns the position of the head
		"""
		return self._position

	def getOtherPositions(self):
		"""
		returns the other positions ocupied by the plane
		"""
		return self._otherPositions

	def validatePlane(self, position, player):
		"""
		checks if every spot of the plane is valid
		input: a Point with the position of the head
		raise: ValueError if at least one of the spots are outside the board
		"""
		if position.x < 0 or position.x > 9:
			raise ValueError("Invalid Plane!")
		if position.y < 0 or position.y > 9:
			raise ValueError("Invalid Plane!")
		if position.x - 3 * self._scalarX < 0 or position.x - 3 * self._scalarX > 9:
			raise ValueError("Invalid Plane!")
		if position.x - 2 * self._scalarY < 0 or position.x + 2 * self._scalarY < 0:
			raise ValueError("Invalid Plane!")
		if position.x - 2 * self._scalarY > 9 or position.x + 2 * self._scalarY > 9:
			raise ValueError("Invalid Plane!")
		if position.y - 3 * self._scalarY < 0 or position.y - 3 * self._scalarY > 9:
			raise ValueError("Invalid Plane!")
		if position.y + 2 * self._scalarX < 0 or position.y - 2 * self._scalarX < 0:
			raise ValueError("Invalid Plane!")
		if position.y + 2 * self._scalarX > 9 or position.y - 2 * self._scalarX > 9:
			raise ValueError("Invalid Plane!")

	def computeOtherPositions(self):
		"""
		computes the other positions aside from the head
		"""
		x = self._position.x
		y = self._position.y
		scalarX = self._scalarX
		scalarY = self._scalarY

		for i in range(1, 4):
			self._otherPositions.append(Point(x - i * scalarX, y - i * scalarY))

		for i in [1, 3]:
			self._otherPositions.append(Point(x - i * scalarX - 1 * scalarY, y - i * scalarY - 1 * scalarX))
			self._otherPositions.append(Point(x - i * scalarX + 1 * scalarY, y - i * scalarY + 1 * scalarX))

		self._otherPositions.append(Point(x - 1 * scalarX - 2 * scalarY, y - 1 * scalarY - 2 * scalarX))
		self._otherPositions.append(Point(x - 1 * scalarX + 2 * scalarY, y - 1 * scalarY + 2 * scalarX))

