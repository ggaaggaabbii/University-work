from texttable import Texttable


class Board:
	strings = {
		0:" ",
		1:"x",
		2:"o"
	}
	def __init__(self):
		self._board = [[0 for x in range(6)] for y in range(6)]

	def __str__(self):
		display = Texttable()
		for i in range(6):
			l = []
			for j in range(6):
				l = l + [Board.strings[self._board[i][j]]]

			display.add_row(l)

		return display.draw()

	def makeMove(self, x, y, val):
		if self._board[x][y] != 0:
			raise Exception("Invalid move")
		if val == "o":
			self._board[x][y] = 2
		else:
			self._board[x][y] = 1

	def getB(self):
		return self._board

	def setOn(self, x, y, val):
		self._board[x][y] = val