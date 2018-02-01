class UI:
	def __init__(self, game):
		self._game = game

	def printMenu(self):
		print("\t A move is made by specifying the position and the placement value (with no space inbetween ex: 11o)")

	def start(self):
		ok = False
		self.printMenu()
		print(self._game.display())
		while self._game.isOver() == False:
			if ok == False:
				ok = True
				self._game.makeAi()
				if self._game.isOver():
					break
			print(self._game.display())
			c = input(">> ")
			try:
				self._game.makeMove(int(c[0]) - 1, int(c[1]) - 1, c[2])
				ok = False
			except Exception as ex:
				print ("Invalid Input")

		print(self._game.display())

		if self._game.gg():
			print("Order wins!")
		else:
			print("Chaos Wins!")