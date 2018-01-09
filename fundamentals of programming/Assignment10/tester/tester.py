import unittest
import sys
sys.path.append('./..')
from Model.plane import Plane
from Model.plane import Point
from Model.board import Board
from Model.ai import Ai
from Game.game import Game

class Tester(unittest.TestCase):
	def testBoard(self):
		b = Board()
		self.assertEquals(b.getFromPosition(0, 0), 0)
		b.setOnPosition(0, 0, 1)
		self.assertEquals(b.getFromPosition(0, 0), 1)
		b.makeMove(Point(1, 2))
		self.assertEquals(b.getFromPosition(1, 2), 4)
		p = Plane(Point(1, 2), 'S', 'Player')
		with self.assertRaises(Exception):
			b.addPlane(p)
		p = Plane(Point(2, 2), 'S', 'Player')
		b.addPlane(p)

	def testPlane(self):
		a = Plane(Point(0, 2), 'S', 'Player')
		for i in [Point(1, 0), Point(1, 1), Point(1, 2), Point(1, 3), Point(1, 4), Point(2, 2), Point(3, 1), Point(3, 2), Point(3, 3)]:
			assert i in a.getOtherPositions()
		with self.assertRaises(Exception):
			a = Plane(Point(0, 2), 'N', 'Player')

	def testGame(self):
		b = Board()
		a = Ai()
		g = Game(b, a)
		self.assertEquals(g.getAiPlaneCount(), 0)
		g.addPlane(0, 2, 'S')
		g.addPlane(0, 7, 'S')
		g.addPlane(4, 6, 'S')
		self.assertEquals(g.getFromPosition(0, 2), 2)
		g.chooseAiPlanes()
		self.assertEquals(g.getAiPlaneCount(), 3)
		while g.isGameWon() == False:
			g.makeAiMove()
		self.assertEquals(g.wonPlayer(), False)


if __name__ == '__main__':
	tests = unittest.TestLoader().discover('.')
	unittest.TextTestRunner(verbosity = 2).run(tests)	
