from Model.ship import Ship
from Model.board import Board
from Model.ship import Point
import random

class Game:
	def __init__(self, bo):
		self._board = bo
		self._pl = 6
		self._al = 6


	def adS(self, l):
		"""
		adds a ship to the board from the given list of positions
		input: the list of positions
		"""
		p1 = Point(l[0].gX(), l[0].gY())
		p2 = Point(l[1].gX(), l[1].gY())
		p3 = Point(l[2].gX(), l[2].gY())

		self._board.aS(Ship(p1, p2, p3, "player"))


	def gFB(self):
		"""
		returns the cheat string
		"""
		return self._board.gFB()

	def isWon(self):
		"""
		returns if the game is won
		"""
		return self._al == 0 or self._pl == 0

	def wonPl(self):
		"""
		returns if the player won the game
		"""
		return self._al == 0

	def gBoard(self):
		"""
		returns the board state
		"""
		return self._board

	def chooseAi(self):
		"""
		if the game can start chooses the ships for the ai
		"""
		if self._board.canS():
			aiShips = 0
			while aiShips != 2:
				try:
					aiShips += 1
					x = random.randint(0, 5)
					y = random.randint(0, 5)
					d = [(-1, 0), (0, -1), (1, 0), (0, 1)]
					orint = d[random.randint(0, 3)]

					p1 = Point(x, y)
					p2 = Point(x + orint[0], y + orint[1])
					p3 = Point(x + 2 * orint[0], y + 2 * orint[1])

					self._board.aS(Ship(p1, p2, p3, "ai"))

				except Exception:
					aiShips -= 1
		else:
			raise Exception("Game can not start yet")

	def makeM(self, l):
		"""
		makes a move for the player
		input: the position
		"""
		p = Point(l[0].gX(), l[0].gY() + 6)
		if self._board.makeMove(p) == True:
			self._al -= 1
			return True
		return False

	def makeMA(self):
		"""
		chooses a random valid move for the ai
		"""
		x = random.randint(0, 5)
		y = random.randint(0, 5)
		while True:
			try:
				if self._board.makeMove(Point(x, y)) == True:
					self._pl -= 1
					return True
				return False
				
			except Exception:
				x = random.randint(0, 5)
				y = random.randint(0, 5)
