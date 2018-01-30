from Model.ship import Point

class UI:
	inp = {
		'A':0,
		'B':1,
		'C':2,
		'D':3,
		'E':4,
		'F':5,
		'0':0,
		'1':1,
		'2':2,
		'3':3,
		'4':4,
		'5':5
	}


	def __init__(self, game):
		self._game = game
		self._isG = False
		self._cmd = ""

	def readCommand(self):
		"""
		reads the command from the user
		"""
		c = input(">> ")
		c = c.split(" ")
		for i in range(len(c)):
			c[i] = c[i].strip()

		if c[0] == "ship":
			if len(c) != 2:
				raise Exception("Invalid command")
			self._cmd = c[0]
			if len(c[1]) != 6:
				raise Exception("Invalid command")
			self._params = []
			for i in c[1]:
				if i not in UI.inp:
					raise Exception("Invalid command")

			self._params.append(Point(UI.inp[c[1][1]], UI.inp[c[1][0]]))
			self._params.append(Point(UI.inp[c[1][3]], UI.inp[c[1][2]]))
			self._params.append(Point(UI.inp[c[1][5]], UI.inp[c[1][4]]))
		elif c[0] == "exit":
			self._cmd = "exit"
			if len(c) != 1:
				raise Exception("Invalid command")
		elif c[0] == "start":
			self._cmd = "start"
			if len(c) != 1:
				raise Exception("Invalid command")
		elif c[0] == "cheat":
			self._cmd = "cheat"
			if len(c) != 1:
				raise Exception("Invalid command")
		elif c[0] == "atack":
			self._cmd = "atack"
			if len(c) != 2:
				raise Exception("Invalid command")
			if len(c[1]) != 2:
				raise Exception("Invalid command")

			for i in c[1]:
				if i not in UI.inp:
					raise Exception("Invalid command")
			
			self._params = []
			self._params.append(Point(UI.inp[c[1][1]], UI.inp[c[1][0]]))

			

	def printB(self):
		print(self._game.gBoard())

	def revealB(self):
		"""
		reveals the board after a cheat command
		"""
		print(self._game.gFB())

	def start(self):
		"""
		starts the main loop of the game
		"""
		while self._game.isWon() == False:
			try:
				self.printB()
				self.readCommand()
				if self._isG == False and self._cmd == 'ship':
					self._game.adS(self._params)
				elif self._isG == False and self._cmd == "start":
					self._game.chooseAi()
					self._isG = True
				elif self._cmd == "exit":
					break
				elif self._isG == True and self._cmd == "cheat":
					self.revealB()
				elif self._isG == True and self._cmd == "atack":
					if self._game.makeM(self._params) == False:
						print("Player misses!")
					else:
						print("Player hits!")
					if self._game.isWon() == False:
						if self._game.makeMA() == False:
							print("Computer misses!")
						else:
							print("Computer hits!")
				else:
					raise Exception("Invalid command")

			except Exception as ex:
				print(ex)
		self.printB()
		if self._game.wonPl():
			print("Player wins")
		else:
			print("Computer wins")
