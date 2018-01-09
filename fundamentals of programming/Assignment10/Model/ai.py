import random
from Model.board import Board
from Model.plane import Point
from Model.plane import Plane

class Ai:
	def __init__(self):
		"""
		initializes the ai with its own board
		"""
		self._moveCounter = 0
		self._board = Board()
		self._updated = False


	def chooseMove(self, currentState):
		"""
		chooses the next move of the ai according to the current state
		if the ai hit less than 4 points from the players planes or made less than 8 moves it chooses randomly
		if not it performs a backtracking check to see how can the player's planes be placed
		input: the current state of the board
		output: a tuple with the position on the board of the chosen move
		"""
		if (self.hitCounter(currentState) <= 3 or self._moveCounter < 8) and self._moveCounter < 21:
			self._board.setOnPosition(0, 0, 4)
			self._board.setOnPosition(0, 9, 4)
			self._board.setOnPosition(9, 0, 4)
			self._board.setOnPosition(9, 9, 4)
			x = random.randint(0, 9)
			y = random.randint(0, 9)
			while self._board.getFromPosition(x, y) != 0:
				x = random.randint(0, 9)
				y = random.randint(0, 9)

			self._board.makeMove(Point(x, y))
			self._moveCounter += 1
			return (x, y)
		else:
			self._moveCounter += 1
			return self.choose(currentState)
	
	def resetBoard(self):
		"""
		resets the state of the board
		"""
		for i in range(10):
			for j in range(10):
				self._board.setOnPosition(i, j, 0)

	def choose(self, currentState):
		"""
		initializes the board with the current obstacles and starts the backtracking algorithm
		input: the current state
		output: a tuple with the position on the board of the chosen move
		"""
		self.resetBoard()
		self._solution = 0
		for i in range(10):
			for j in range(10):
				if currentState[i][j] != 5 and currentState[i][j] != 6:
					self._board.setOnPosition(i, j, currentState[i][j])

		self.bktr(0, currentState)

		return self._solution[random.randint(0, len(self._solution) - 1)]

	def bktr(self, step, currentState):
		"""
		performs the backtracking algorithm
		input: the current step of the recursion, the current state of the board
		"""
		self._moveCounter += 1
		if self._solution != 0:
			return
		if step == 3:
			if self.ckeckCover(currentState):
				self._solution =  self.getAPosition(currentState)
			else:
				return
	
		for i in range(10):
			for j in range(10):
				for k in ['N', 'S', 'E', 'W']:
					try:
						toAdd = Plane(Point(i, j), k, "Player")
					except Exception:
						continue
					try:
						self._board.addPlane(toAdd)
					except Exception:
						continue
					self.bktr(step + 1, currentState)
					for l in toAdd.getOtherPositions():
						self._board.setOnPosition(l.x, l.y, 0)
					self._board.setOnPosition(i, j, 0)


	def ckeckCover(self, currentState):
		"""
		checks for a found solution if all the previous hit positions are covered on the current plane configuration
		input: the current state of the board
		output: true if all the previous hit positions are covered
				false otherwise
		"""
		for i in range(10):
			for j in range(10):
				if currentState[i][j] == 5 or currentState[i][j] == 6:
					if self._board.getFromPosition(i, j) != currentState[i][j] - 4:
						return False
		return True

	def getAPosition(self, currentState):
		"""
		computes a list with tuples of the posible positions of the heads of the planes
		input: the current board state
		output: the list
		"""
		sol = []
		for i in range(10):
			for j in range(10):
				if self._board.getFromPosition(i, j) == 2 and currentState[i][j] != 6:
					sol.append((i, j))
		return sol

	def hitCounter(self, currentState):
		"""
		counts the positions on which the ai got a hit
		input: the current state of the board
		output: the number of hits
		"""
		counter = 0
		for i in range(10):
			for j in range(10):
				if currentState[i][j] == 5 or currentState[i][j] == 6:
					counter += 1
		return counter

