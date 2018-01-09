from Game.game import Game
import random

class UI:

	coordonates = {'a':0, 'b': 1, 'c': 2,'d': 3,'e': 4,'f': 5,'g': 6,'h': 7,'i': 8,'j': 9}

	def printLegend(self):
		print("\tWelcome to The Airplanes Game!")
		print("")
		print("\tYou will need to first choose the position of your palnes. To do that you simply type in the position on board and the orientation of the tail of the plane.(ex: a 2 S - to place the plane on the a 2 position ortiented downwords)")
		print("After that the game starts.")
		print("You will than need to select the place you want to atack by specifying the position as before.")
		print("The game continues until one of the palyers has no planes remaining.")
		print("ASCIIs for the board: ")
		print("@ - head of the plane")
		print("# - part of the plane")
		print("o - damaged part of the plane")
		print("X - damaged head of the plane")
		print(". - empty spot")


	def readPlane(self):
		plane = input("Introduce the plane: ")
		plane = plane.split(' ')
		if len(plane) != 3:
			raise TypeError("Invalid plane!")
		for i in range(3):
			plane[i] = plane[i].strip()
		return plane

	def __init__(self, game):
		self._game = game

	def readMove(self):
		move = input("Introduce a position: ")
		move = move.split(' ')
		if len(move) != 2:
			raise TypeError("Invalid move!")
		for i in range(2):
			move[i] = move[i].strip()
		return move

	def choosePlayerPlanes(self):
		counter = 0
		while counter != 3:
			try:
				counter += 1
				plane = self.readPlane()
				self._game.addPlane(UI.coordonates[plane[0]], int(plane[1]), plane[2])
				print (self._game.getBoardState())
			except Exception as ex:
				print ("Invalid plane!")
				counter -= 1

	def start(self):
		self.printLegend()
		print (self._game.getBoardState())
		self.choosePlayerPlanes()
		self._game.chooseAiPlanes()
		currentPlayer = random.randint(1, 2)
		while not self._game.isGameWon():
			try:
				if currentPlayer == 1:
					move = self.readMove()
					self._game.makeMove(UI.coordonates[move[0]], int(move[1]))
					currentPlayer = 2
				else:
					self._game.makeAiMove()
					currentPlayer = 1
				print (self._game.getBoardState())
			except Exception as ex:
				print (ex)
				print("Invalid move!")

		print(self._game.getBoardState())

		if self._game.wonPlayer():
			print("Player Wins!")
		else:
			print("Game Over")
