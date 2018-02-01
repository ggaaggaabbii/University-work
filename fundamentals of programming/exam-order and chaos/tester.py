import unittest
from Model.board import Board
from Model.ai import Ai
from Game.game import Game
from ui.ui import UI

class tester(unittest.TestCase):
	def test(self):
		b = Board()
		a = Ai(b)
		g = Game(b, a)

		g.makeMove(0, 0, "o")
		g.makeMove(0, 1, "o")
		g.makeMove(0, 2, "o")
		g.makeMove(0, 3, "o")
		g.makeMove(0, 4, "o")

		self.assertEqual(g.gg(), True)

		b = Board()
		a = Ai(b)
		g = Game(b, a)

		g.makeMove(0, 0, "o")
		g.makeMove(1, 0, "o")
		g.makeMove(2, 0, "o")
		g.makeMove(3, 0, "o")
		g.makeMove(4, 0, "o")

		self.assertEqual(g.gg(), True)

		b = Board()
		a = Ai(b)
		g = Game(b, a)

		g.makeMove(0, 0, "o")
		g.makeMove(1, 1, "o")
		g.makeMove(2, 2, "o")
		g.makeMove(3, 3, "o")
		g.makeMove(4, 4, "o")

		self.assertEqual(g.gg(), True)

		b = Board()
		a = Ai(b)
		g = Game(b, a)

		g.makeMove(0, 5, "o")
		g.makeMove(1, 4, "o")
		g.makeMove(2, 3, "o")
		g.makeMove(3, 2, "o")
		g.makeMove(4, 1, "o")

		self.assertEqual(g.gg(), True)

		b = Board()
		a = Ai(b)
		g = Game(b, a)

		g.makeMove(0, 5, "o")
		g.makeMove(1, 4, "o")
		g.makeMove(5, 3, "o")
		g.makeMove(3, 2, "o")
		g.makeMove(4, 1, "o")

		self.assertEqual(g.gg(), False)


if __name__ == '__main__':
	unittest.main()