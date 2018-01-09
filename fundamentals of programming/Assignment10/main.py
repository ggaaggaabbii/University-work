from Model.board import Board
from Model.plane import Plane
from Model.plane import Point
from Model.ai import Ai
from Game.game import Game
from ui.ui import UI
from ui.gui import GUI

def main():
	board = Board()
	ai = Ai()
	game = Game(board, ai)

	choice = 0
	while choice != "y" and choice != "n":
		choice = input("Do you want to proceed with the graphical user interface? [y/n] ")

	if choice == "y":
		ui = GUI(game)
	else:
		ui = UI(game)
	ui.start()

main()
