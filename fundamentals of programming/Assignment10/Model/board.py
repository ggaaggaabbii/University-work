from Model.texttable import Texttable
from Model.plane import Plane
from Model.plane import Point

class Board:

	displayStrings = {0:" ", 1:"#", 2:"@", 4:".", 5:"o", 6:"X"}

	def __init__(self):
		"""
		initializes the board with 0 on each position
		"""
		self._board = [[0 for x in range(20)] for y in range(10)]

	def __str__(self):
		"""
		computes the string coresponding to the current state of the board
		output: the coresponding string
		"""
		t = Texttable()
		a = [0, 1, 2, 3, 4 ,5 , 6, 7, 8, 9]
		t.add_row([' '] + a + [' '] + a)
		a = 97
		for x in self._board:
			row = []
			row.append(chr(a))
			for y in x[:10]:
				row.append(Board.displayStrings[y])
			row.append(chr(a))
			for y in x[10:]:
				if y != 1 and y != 2:
					row.append(Board.displayStrings[y])
				else:
					row.append(' ')
			t.add_row(row)
			a += 1
		return t.draw()

	def addPlane(self, plane):
		"""
		adds a plane to the board
		input: a plane
		"""
		self.checkValid(plane)
		self._board[plane.getPosition().x][plane.getPosition().y] = 2
		for i in plane.getOtherPositions():
			self._board[i.x][i.y] = 1

	def checkValid(self, plane):
		"""
		checks if a plane can be added to the board
		input: a plane
		raise: ValueError if there is something already on the board on one of the plane's positions
		"""
		for i in plane.getOtherPositions():
			if self._board[i.x][i.y] != 0:
				raise ValueError("Spot already taken!")
		if self._board[plane.getPosition().x][plane.getPosition().y] != 0:
			raise ValueError("Spot already taken!")

	def makeMove(self, position):
		"""
		performes a move on a given position
		input: a Point with the coordonates of the move
		raise: ValueError if the move can not be performed
		"""
		if self._board[position.x][position.y] > 3:
			raise ValueError("Position unavailable!")
		else:
			self._board[position.x][position.y] += 4

	def getFromPosition(self, x, y):
		"""
		gets the value from the board from the x, y position
		input: a x, y position
		output: the value from the x, y position
		"""
		return self._board[x][y]

	def setOnPosition(self, x, y, value):
		"""
		sets the value on a position
		input: the x, y position and the value
		"""
		self._board[x][y] = value
