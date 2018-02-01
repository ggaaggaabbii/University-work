import random


class Ai:
	def __init__(self, board):
		self._board = board
		self._ind = [[-1, -1], [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1]]

	def makeMove(self):
		bo = self._board.getB()
		maxim = 0
		sol = []
		
		val1, val2 = self.getCount()

		for i in range(6):
			for j in range(6):
				if bo[i][j] == 0:
					a = self.check(i, j, val1)
					b = self.check(i, j, val2)
					if a == maxim:
						sol += [[i, j, val1]]

					if a > maxim:
						maxim = a
						sol = [[i, j, val1]]

					if b == maxim:
						sol += [[i, j, val2]]

					if b > maxim:
						maxim = b
						sol = [[i, j, val2]]

		pos = sol[random.randint(0, len(sol) - 1)]

		self._board.setOn(pos[0], pos[1], pos[2])



	def check(self, x, y, val):
		b = self._board.getB()
		nr = 0

		for i in self._ind:
			if x + i[0] >= 0 and x + i[0] <= 5 and y + i[1] >= 0 and y + i[1] <= 5:
				if b[x + i[0]][y + i[1]] == val:
					nr += 1
		return nr


	def getCount(self):

		bo = self._board.getB()

		xc = 0
		oc = 0

		for i in range(6):
			for j in range(6):
				if bo[i][j] == 1:
					xc += 1
				elif bo[i][j] == 2:
					oc += 1

		if xc > oc:
			val1 = 1
			val2 = 1
		elif xc == oc:
			val1 = 1
			val2 = 2
		else:
			val1 = 2
			val2 = 2

		return val1, val2

	
