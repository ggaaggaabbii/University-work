import unittest
from Model.ship import Ship
from Model.board import Board
from Model.ship import Point
from Game.game import Game

class tester(unittest.TestCase):
	def testShip(self):
		p1 = Point(0, 1)
		p2 = Point(0, 2)
		p3 = Point(0, 3)
		s = Ship(p1, p2, p3, "player")
		p2 = Point(0, 4)

		with self.assertRaises(Exception):
			s = Ship(p1, p2, p3)

		p2 = Point(-1, 1)
		with self.assertRaises(Exception):
			s = Ship(p1, p2, p3)

		p2 = Point(1, 1)
		with self.assertRaises(Exception):
			s = Ship(p1, p2, p3)

	def testBoard(self):
		p1 = Point(0, 1)
		p2 = Point(0, 2)
		p3 = Point(0, 3)
		s = Ship(p1, p2, p3, "player")
		b = Board()
		b.aS(s)

		p1 = Point(1, 1)
		p2 = Point(1, 2)
		p3 = Point(1, 3)
		s = Ship(p1, p2, p3, "player")
		b.aS(s)

		p1 = Point(3, 1)
		p2 = Point(3, 2)
		p3 = Point(3, 3)
		s = Ship(p1, p2, p3, "player")
		b.aS(s)
		with self.assertRaises(Exception):
			b.aS(s)
	
	def testGame(self):
		b1 = Board()
		g = Game(b1)

		p1 = Point(0, 1)
		p2 = Point(0, 2)
		p3 = Point(0, 3)
		
		g.adS((p1, p2, p3))

		p1 = Point(1, 1)
		p2 = Point(1, 2)
		p3 = Point(1, 3)
		
		g.adS((p1, p2, p3))
		p1 = Point(3, 1)
		p2 = Point(3, 2)
		p3 = Point(3, 3)

		g.adS((p1, p2, p3))

		with self.assertRaises(Exception):
			g.adS((p1, p2, p3))

		g.chooseAi()
		while g.isWon() == False:
			g.makeMA()

		self.assertEqual(g.isWon(), True)


if __name__ == '__main__':
	unittest.main()