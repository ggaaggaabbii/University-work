class Point:

	def __init__(self, x, y):
		self._x = x
		self._y = y

	def __eq__(self, other):
		return self._x == other._x and self._y == other._y

	def __str__(self):
		return str(self._x) + " " + str(self._y)

	def gX(self):
		return self._x

	def gY(self):
		return self._y

class Ship:

	def __init__(self, poz1, poz2, poz3, player):

		self.validate(poz1, poz2, poz3)
		self._player = player
		self._poz1 = poz1
		self._poz2 = poz2
		self._poz3 = poz3

		if player == "ai":
			self._poz1._y += 6
			self._poz2._y += 6
			self._poz3._y += 6

	def validate(self, poz1, poz2, poz3):
		"""
		tests the ship, if it is in the correct order, inside the board
		input: the 3 positions of the ship
		raise: ValueError if not correct
		"""
		if poz1.gX() < 0 or poz1.gX() > 6:
			raise ValueError("Not a good ship")
		if poz1.gY() < 0 or poz1.gY() > 6:
			raise ValueError("Not a good ship")
		if poz2.gX() < 0 or poz2.gX() > 6:
			raise ValueError("Not a good ship")
		if poz2.gY() < 0 or poz2.gY() > 6:
			raise ValueError("Not a good ship")
		if poz3.gX() < 0 or poz3.gX() > 6:
			raise ValueError("Not a good ship")
		if poz3.gY() < 0 or poz3.gY() > 6:
			raise ValueError("Not a good ship")
		if poz1 == poz2 or poz1 == poz3 or poz2 == poz3:
			raise ValueError("Not a good ship")
		l = [poz1, poz2, poz3]
		for i in range(3):
			for j in range(i + 1, 3):
				if l[i].gX() < l[j].gX() or (l[i].gX() == l[j].gX() and l[i].gY() < l[j].gY()):
					l[i], l[j] = l[j], l[i]
		
		if l[1].gX() != (l[0].gX() + l[2].gX()) / 2:
			raise ValueError("Not a good ship")
		if l[1].gY() != (l[0].gY() + l[2].gY()) / 2:
			raise ValueError("Not a good ship")
		if l[1].gY() - l[2].gY() > 1:
			raise ValueError("Not a good ship")
		if l[1].gX() - l[2].gX() > 1:
			raise ValueError("Not a good ship")

	def gPos(self):
		"""
		returns a list with the positions of the ship
		"""
		return (self._poz1, self._poz2, self._poz3)

	def gP(self):
		"""
		returns the playert owning the ship
		"""
		return self._player
