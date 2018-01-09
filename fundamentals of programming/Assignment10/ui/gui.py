from tkinter import *
import sys
sys.path.append("./..")
from Model.plane import Point
import time

class GUI:

	toDisplay = {
				1:lambda self, x, y, z, t: self._canvas.create_oval(x + 7, y + 2, z - 2, t - 2, fill = "light green"),
				2:lambda self, x, y, z, t: self._canvas.create_oval(x + 7, y + 2, z - 2, t - 2, fill = "#FFA07A"),
				4:lambda self, x, y, z, t: self._canvas.create_oval(x + 17, y + 12, z - 12, t - 12, fill = "#f2f2f2"), 
				5:lambda self, x, y, z, t: self._canvas.create_oval(x + 17, y + 12, z - 12, t - 12, fill = "#228B22"), 
				6:lambda self, x, y, z, t: self._canvas.create_oval(x + 17, y + 12, z - 12, t - 12, fill = "#8B0000"),
				}

	def __init__(self, game):
		self._game = game
		self.showInstructions()
		self._root = Tk()
		self._root.title("Airplanes")
		self._width = 885
		self._height = 520
		self._planes = 0
		self._canvas = Canvas(self._root, width = self._width, height = self._height, 
								bg = "light grey")
		self._canvas.bind("<Button-1>", self.makeMove)
		self.drawBoard()
		self._canvas.grid(column = 0, padx = 10, pady = 10)

	def drawBoard(self):
		self._scaleX = self._height // 11
		self._scaleY = self._width // 22
		self._canvas.create_rectangle(0, 0, self._width, self._height, fill = "light grey")
						
		for i in range(11):
			for j in range(22):
				self._canvas.create_rectangle(j * self._scaleY + 2, i * self._scaleX + 2,
											(j + 1) * self._scaleY + 2, (i + 1) * self._scaleX,
											fill = "light blue")
		a = 97
		for i in range(1, 11):
			self._canvas.create_text(self._scaleY // 2, i * self._scaleX + 30, text = chr(a))
			self._canvas.create_text(self._scaleY * 11 + self._scaleY // 2, i * self._scaleX + 30,
									 text = chr(a))
			a += 1

		for i in range (10):
			self._canvas.create_text(self._scaleY * (i + 1) + 20, 30, text = str(i))

		for i in range (10):
			self._canvas.create_text(self._scaleY * (i + 12) + 20, 30, text = str(i))


	def choosePlane(self, x, y):
		try:
			newY = (x - self._scaleY) // self._scaleY
			newX = (y - self._scaleX) // self._scaleX
			x = newX
			y = newY
			direction = Tk()
			direction.title("Orientation")
			north = Button(direction, text="N", width = 20, 
							command = lambda: self.selectDirection(Point(x, y), direction, "N")).pack()
			south = Button(direction, text="S", width = 20, 
							command = lambda: self.selectDirection(Point(x, y), direction, "S")).pack()
			west = Button(direction, text="W", width = 20, 
							command = lambda: self.selectDirection(Point(x, y), direction, "W")).pack()
			east = Button(direction, text="E", width = 20, 
							command = lambda: self.selectDirection(Point(x, y), direction, "E")).pack()
			direction.mainloop()
		except Exception:
			pass

	def selectDirection(self, position, app, dir):
		app.destroy()
		self._game.addPlane(position.x, position.y, dir)
		self._planes += 1
		if self._game.getAiPlaneCount() != 3 and self._planes == 3:
					self._game.chooseAiPlanes()
		self.updateInterface()

	def updateInterface(self):
		for i in range(10):
			for j in range(10):
				b = self._game.getFromPosition(i, j)
				if b != 0:
					GUI.toDisplay[b](self, (j + 1) * self._scaleY, (i + 1) * self._scaleX,
									(j + 2) * self._scaleY, (i + 2) * self._scaleX)

		for i in range(10):
			for j in range(10):
				b = self._game.getFromPosition(i, j + 10)
				if b != 0 and b != 1 and b != 2:
					GUI.toDisplay[b](self, (j + 12) * self._scaleY, (i + 1) * self._scaleX,
									(j + 13) * self._scaleY, (i + 2) * self._scaleX)

	def makeMove(self, event):
		try:
			if self._planes < 3:
				self.choosePlane(event.x, event.y)
			else:
				y = (event.x - self._scaleY * 12) // self._scaleY
				x = (event.y - self._scaleX) // self._scaleX
				if x < 0 or y < 0:
					return
				self._game.makeMove(x, y)
				self.updateInterface()
				if self._game.isGameWon():
					self.win()
					return
				self._game.makeAiMove()
				self.updateInterface()
				if self._game.isGameWon():
					self.gameOver()
					return
			
		except Exception as ex:
			pass

	def gameOver(self):
		lose = Tk()
		lose.title("Game Over!")
		message = Label(lose, text = "Game Over!", font=("Helvetica", 16)).pack()
		quit = Button(lose, text = "Okay!", command = lambda:(lose.destroy(), self._root.destroy())).pack()
		lose.mainloop()

	def win(self):
		win = Tk()
		win.title("Win!")
		message = Label(win, text = "Player Wins!", font=("Helvetica", 16)).pack()
		quit = Button(win, text = "Okay!", command = lambda:(win.destroy(), self._root.destroy())).pack()
		win.mainloop()

	def showInstructions(self):
		instructions = Tk()
		bt = Button(instructions, text = "Dismiss!", width = 20, 
					command = lambda: instructions.destroy()).grid(row = 1, column = 0, padx = 10, pady = 10)
		instructions.title("Instructions")
		message = Label(instructions, text = "Welcome to The Airplanes Game!\n" + 
						"\n" + 
						"\tYou will need to first choose the position of your palnes. To do that you simply click on the position on board and than select the orientation of the plane.\t\n" + 
						"After that the game starts.\n" + 
						"You will than need to select the place you want to atack by clicking on the position on the board.\n" + 
						"The game continues until one of the palyers has no planes remaining.\n" + 
						"The left side is where you choose the planes.",
						 font=("Helvetica", 12)).grid(row = 0, column = 0, padx = 10, pady = 10)
		instructions.mainloop()

	def start(self):
		self._root.mainloop()
		
		
