from Model.ship import Ship
from Model.board import Board
from Model.ship import Point
from Game.game import Game
from ui.ui import UI

if __name__ == '__main__':
	b = Board()
	g = Game(b)
	u = UI(g)
	u.start()