from Model.board import Board
from Model.ai import Ai
from Game.game import Game
from ui.ui import UI

if __name__ == '__main__':
	b = Board()
	a = Ai(b)
	g = Game(b, a)
	u = UI(g)
	u.start()

