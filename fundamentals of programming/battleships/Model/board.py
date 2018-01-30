from Model.ship import Ship


class Board:

	strings = {
		0:".",
		1:"o",
		2:"+",
		3:"x"
	}

	def __init__(self):
		self._board = [[0 for x in range(12)] for y in range(6)]
		self._ships = []

	def __str__(self):
		"""
		the string to be displayed each turn
		"""
		s = ""
		s += " ABCDEF ABCDEF\n"
		a = 0
		for i in range(6):
			s += str(a)
			for j in range(6):
				s += str(Board.strings[self._board[i][j]])

			s += str(a)

			for j in range(6, 12):
				if self._board[i][j] != 2:
					s += str(Board.strings[self._board[i][j]])
				else:
					s += "."

			s += "\n"
			a += 1

		return s

	def gFB(self):
		"""
		reveals the board
		"""
		s = ""
		s += " ABCDEF ABCDEF\n"
		a = 0
		for i in range(6):
			s += str(a)
			for j in range(6):
				s += str(Board.strings[self._board[i][j]])

			s += str(a)

			for j in range(6, 12):
				s += str(Board.strings[self._board[i][j]])

			s += "\n"
			a += 1

		return s

	def delS(self, s):
		"""
		removes a ship from the board
		input: the ship
		"""
		for i in s.gPos():
			self._board[i.gX()][i.gY()] = 0

	def aS(self, s):
		"""
		adds a ship to the board
		input: the ship
		raise: error if the ship can not be added
		"""
		sh = 0
		if len(self._ships) == 2 and s.gP() != "ai":
			self.delS(self._ships[0])
			sh = self._ships[0]
			self._ships.remove(self._ships[0])

		try:
			for i in s.gPos():
				if self._board[i.gX()][i.gY()] != 0:
					raise ValueError ("Invalid ship")

			for i in s.gPos():
				self._board[i.gX()][i.gY()] = 2


			self._ships.append(s)

		except Exception as ex:
			if isinstance(sh, Ship):
				self.aS(sh)
			raise Exception("Invalid Ship")


	def makeMove(self, pos):
		"""
		makes a move
		input: the position
		output: true or false if hit or not
		raise: Exception if the move can not be made
		"""
		if self._board[pos.gX()][pos.gY()] != 0 and self._board[pos.gX()][pos.gY()] != 2:
			raise Exception("Invalid move")
		self._board[pos.gX()][pos.gY()] += 1
		if self._board[pos.gX()][pos.gY()] == 1:
			return False
		return True

	def canS(self):
		"""
		checks if the game can start
		"""
		return len(self._ships) == 2
