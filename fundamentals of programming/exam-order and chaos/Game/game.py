import random

class Game:
	def __init__(self, board, ai):
		self._board = board
		self._ai = ai

	def display(self):
		return str(self._board)

	def makeMove(self, x, y, val):
		if val != "o" and val != "x":
			raise Exception("Invalid move")
		if x < 0 or x > 5:
			raise Exception("Invalid move")
		if y < 0 or y > 5:
			raise Exception("Invalid move")
		self._board.makeMove(x, y, val)


	def gg(self):
		"""
		checks if order wins with a formation of 5
		checks  the rows
				the collums
				the diagonals
		output: true if there is a formation on any of the rows cols or diags
				false otherwise
		"""

		if self.checkR() == True:
			return True
		if self.checkC() == True:
			return True
		return self.checkD()

	def checkR(self):
		"""
		checks if there is a formation of 5 on any row
		output: true if there is 
				false if not
		"""
		b = self._board.getB()

		for i in range(0, 6):
			oc = 0
			xc = 0
			for j in range(0, 6):
				if b[i][j] == 1:
					oc = 0
					xc += 1
				elif b[i][j] == 2:
					xc = 0
					oc += 1
				else:
					xc = 0
					oc = 0
				if xc == 5 or oc == 5:
					return True
		return False

	def checkC(self):
		"""
		checks if there is a formation of 5 on any collum
		output: true if there is 
				false if not
		"""
		b = self._board.getB()

		for i in range(0, 6):
			oc = 0
			xc = 0
			for j in range(0, 6):
				if b[j][i] == 1:
					oc = 0
					xc += 1
				elif b[j][i] == 2:
					xc = 0
					oc += 1
				else:
					xc = 0
					oc = 0
				if xc == 5 or oc == 5:
					return True


	def checkD(self):
		"""
		checks if there is a formation on any of the diagonals
		output: true if there is 
				false if not
		"""
		a = False
		for i in range(6):
			a = a or self.checkDig(0, i, "l")
			a = a or self.checkDig(i, 5, "l")
			a = a or self.checkDig(0, i, "r")
			a = a or self.checkDig(i, 0, "r")
		return a

	def checkDig(self, x, y, way):
		"""
		checks if there is a formation of 5 on a diagola
		input: the starting position of the diagonal(x, y), the orintation of it
		output: true if there is a formation of 5
				false if not
		"""
		b = self._board.getB()
		oc = 0
		xc = 0
		if way == "r":
			indX = 1
			indY = 1
		else:
			indX = 1
			indY = -1
		while x >= 0 and y >= 0 and x <= 5 and y <= 5:
			if b[x][y] == 1:
				oc = 0
				xc += 1
			elif b[x][y] == 2:
				xc = 0
				oc += 1
			else:
				xc = 0
				oc = 0
			if xc == 5 or oc == 5:
					return True
			x += indX
			y += indY
		return False

	def isOver(self):
		if self.gg():
			return True
		if self.wonC():
			return True
		return False

	def makeAi(self):
		if self.canWin():
			return
		self._ai.makeMove()

	def canWin(self):
		b = self._board.getB()
		for i in range(6):
			for j in range(6):
				if b[i][j] == 0:
					b[i][j] = 1
					if self.gg():
						return True
					b[i][j] = 2
					if self.gg():
						return True
					b[i][j] = 0
		return False



	def wonC(self):
		b = self._board.getB()

		for i in range(0, 6):
			for j in range(0, 6):
				if b[i][j] == 0:
					return False

		return True