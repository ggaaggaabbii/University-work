from Model.board import Board
from Model.plane import Plane
from Model.plane import Point
import random

class Game:
	playerPlanes = 3
	aiPlanes = 0
	def __init__(self, board, ai):
		"""
		initializes the game with a given board and an ai
		input: the board and the ai
		"""
		self._board = board
		self._ai = ai

	def getFromPosition(self, x, y):
		"""
		returns the state of the board on a given position
		input: the x, y position
		output: the state of the board on that position
		"""
		return self._board.getFromPosition(x, y)

	def getBoardState(self):
		"""
		returns the string of the current board state
		output: the board state
		"""
		return str(self._board)

	def getAiPlaneCount(self):
		"""
		gets the count of the remaining planes of the ai
		output: the ai plane count
		"""
		return Game.aiPlanes

	def addPlane(self, x, y, orientation):
		"""
		adds a plane on a given position with a given orientation
		input: a x, y position and a orientation
		"""
		self._board.addPlane(Plane(Point(x, y), orientation.upper(), 'Player'))

	def chooseAiPlanes(self):
		"""
		chooses the planes for the ai
		"""
		orientations = ['N', 'S', 'E', 'W']
		while Game.aiPlanes != 3:
			try:
				startX = random.randint(0, 10)
				startY = random.randint(0, 10)
				orient = random.randint(0, 4)
				Game.aiPlanes += 1
				self._board.addPlane(Plane(Point(startX, startY), orientations[orient], 'Ai'))
			except Exception:
				Game.aiPlanes -= 1

	def makeMove(self, x, y):
		"""
		makes a move on a given position
		input: the x, y position
		"""
		y += 10
		self._board.makeMove(Point(x, y))
		if self._board.getFromPosition(x, y) == 6:
			Game.aiPlanes -= 1

	def makeAiMove(self):
		"""
		makes a move for the ai
		"""
		pos = self._ai.chooseMove(self.getPlayerBoard())
		self._board.makeMove(Point(pos[0], pos[1]))
		if self._board.getFromPosition(pos[0], pos[1]) == 6:
			Game.playerPlanes -= 1

	def getPlayerBoard(self):
		"""
		gets the current board state of the user
		output: the matrix coresponding to the current state
		"""
		currentState = []
		for i in range(10):
			currentState.append([])
			for j in range(10):
				if self._board.getFromPosition(i, j) != 1 and self._board.getFromPosition(i, j) != 2:
					currentState[i].append(self._board.getFromPosition(i, j))
				else:
					currentState[i].append(0)
		return currentState

	def isGameWon(self):
		"""
		checks if the game is won
		output: true if the game is won
				false otherwise
		"""
		if Game.playerPlanes == 0 or Game.aiPlanes == 0:
			return True
		return False

	def wonPlayer(self):
		"""
		checks if the player won the game
		output: true if the player won
				false otherwise
		"""
		return Game.aiPlanes == 0
