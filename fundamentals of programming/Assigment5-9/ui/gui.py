from controller.controller import controller
from tkinter import *

class GUI:

	def __init__(self, controller):
		self._controller = controller
		self._root = Tk()
		self._menu = Menu(self._root)
		self.fileInit()
		self.addInit()
		self.removeInit()
		self.updateInit()
		self.optionInit()
		self.viewInit()
		self.aboutInit()
		self._input = Entry(self._root)
		self._input.pack(fill = BOTH, padx = 50, pady = 4)
		self._root.geometry("1240x720")
		self._output = Listbox(self._root)
		self._output.pack(fill = BOTH, expand = 1, padx = 4, pady = 4)
		self._root.config(menu = self._menu)
		self._root.title("Movie Rental Application")

	def aboutInit(self):
		self._menu.add_command(label = "About", command = self.printAbout)

	def printAbout(self):
		s = ""
		s += "The input for each command in the option tab:\n"
		s += "\tadd client : <id client>, <client name>\n"
		s += "\tadd movie : <id movie>, <title>, <description>, <genre>\n"
		s += "\tupdate client : <id client>, <client name>\n"
		s += "\tupdate movie : <id movie>, <new title>, <new description>, <new genre>\n"
		s += "\tremove client : <id client>\n"
		s += "\tremove movie : <id movie>\n"
		s += "\trent : <id client>, <id movie>, <rent date(dd/mm/yyyy)>, <due date(dd/mm/yyyy)>\n"
		s += "\treturn : <id rent>, <date(dd/mm/yyyy)>\n"
		s += "\tsearch : <search string>\n"
		s += "\tlate rentals : <date(dd/mm/yyyy)>"
		
		dialog = Toplevel(height = 100, width = 100)
		dialog.title("About")
		msg = Message(dialog, text = s, padx = 4, pady = 4, width = 1000)
		msg.pack()

		btn = Button(dialog, text = "Dismiss", command = dialog.destroy)
		btn.pack()

	def viewInit(self):
		"""
		view menu
		"""
		self._viewMenu = Menu(self._menu, tearoff = 0)
		self._viewMenu.add_command(label = "Clients", command = self.showClients)
		self._viewMenu.add_command(label = "Movies", command = self.showMovies)
		self._viewMenu.add_command(label = "Rentals", command = self.showRentals)
		self._viewMenu.add_command(label = "Most active clients", command = self.showMostActive)
		self._viewMenu.add_command(label = "Most rented movies", command = self.showMostRented)
		self._viewMenu.add_command(label = "Rentals and rented movies", command = self.showAllRentals)
		self._menu.add_cascade(label = "View", menu = self._viewMenu)

	def addInit(self):
		"""
		add menu
		"""
		self._addMenu = Menu(self._menu, tearoff = 0)
		self._addMenu.add_command(label = "Client", command = self.addClient)
		self._addMenu.add_command(label = "Movie", command = self.addMovie)
	
	def fileInit(self):
		"""
		file menu
		"""
		self._fileMenu = Menu(self._menu, tearoff = 0)
		self._fileMenu.add_command(label = "Quit", command = self.quit)
		self._menu.add_cascade(label = "File", menu = self._fileMenu)
	
	def optionInit(self):
		"""
		option menu
		"""
		self._optionMenu = Menu(self._menu, tearoff = 0)
		self._optionMenu.add_cascade(label = "Add", menu = self._addMenu)
		self._optionMenu.add_cascade(label = "Remove", menu = self._removeMenu)
		self._optionMenu.add_cascade(label = "Update", menu = self._updateMenu)
		self._optionMenu.add_command(label = "Rent", command = self.rent)
		self._optionMenu.add_command(label = "Return", command = self.Return)
		self._optionMenu.add_command(label = "Search", command = self.showSearch)
		self._optionMenu.add_command(label = "Late rentals", command = self.showLateRentals)
		self._optionMenu.add_command(label = "Undo", command = self.undo)
		self._optionMenu.add_command(label = "Redo", command = self.redo)
		self._menu.add_cascade(label = "Option", menu = self._optionMenu)

	def removeInit(self):
		self._removeMenu = Menu(self._menu, tearoff = 0)
		self._removeMenu.add_command(label = "Client", command = self.removeClient)
		self._removeMenu.add_command(label = "Movie", command = self.removeMovie)

	def updateInit(self):
		self._updateMenu = Menu(self._menu, tearoff = 0)
		self._updateMenu.add_command(label = "Client", command = self.updateClient)
		self._updateMenu.add_command(label = "Movie", command = self.updateMovie)

	def quit(self):
		self._root.quit()

	def start(self):
		self._root.mainloop()

	def showClients(self):
		self._output.delete(0, END)
		clients = self._controller.listClients()
		if len(clients.keys()) == 0:
			self._output.insert(END, "List is Empty")
		for i in clients.keys():
			self._output.insert(END, "  " + str(clients[i]).strip())
	
	def showMovies(self):
		movies = self._controller.listMovies()
		self.showList(movies)
	
	def showRentals(self):
		rents = self._controller.listRents("")
		self.showList(rents)

	def showList(self, List):
		self._output.delete(0, END)
		if len(List.keys()) == 0:
			self._output.insert(END, "List is Empty")
		for i in List.keys():
			toShow = str(List[i])
			toShow = toShow.split('\n')
			for j in toShow:
				self._output.insert(END, j.strip())
			self._output.insert(END, "")
	
	def showMostRented(self):
		self._output.delete(0, END)
		List = self._controller.getMostRented()
		if len(List[0]) == 0:
			self._output.insert(END, "List is Empty")
			return
		self._output.insert(END, "The most rented movies are:")
		self._output.insert(END, "-" * 720)
		for i in List[0]:
			s = "  ID: " + str(i[0].getID()).ljust(10 - len(str(i[0].getID())))
			s += str(i[0].getTitle()).ljust(70 - len(str(i[0].getTitle()).strip()) // 2)
			s += " rented " + str(i[1]).ljust(10 - len(str(i[1]))) + " times"
			self._output.insert(END, s)
		self._output.insert(END, "-" * 720)
		for i in List[1]:
			s = "  ID: " + str(i[0].getID()).ljust(10 - len(str(i[0].getID())))
			s += str(i[0].getTitle()).ljust(70 - len(str(i[0].getTitle()).strip()) // 2)
			self._output.insert(END,s + " rented for " + str(i[1]).ljust(5) + " days")

	def showMostActive(self):
		self._output.delete(0, END)
		List = self._controller.getMostActive()
		if len(List) == 0:
			self._output.insert(END, "The list is empty")
			return
		self._output.insert(END, "The most active clients are: ")
		self._output.insert(END, "-" * 720)
		for i in List:
			s = "  ID: " + str(i[0].getID()).ljust(10 - len(str(i[0].getID())))
			self._output.insert(END, s + str(i[0].getName()).ljust(50) + " rented movies for " + str(i[1]).ljust(5) + " days")

	def showAllRentals(self):
		self._output.delete(0, END)
		List = self._controller.getAllRentals()
		if len(List[0]) == 0:
			self._output.insert(END, "No rentals")
			return
		self._output.insert(END, "The rentals are:")
		self._output.insert(END, "-" * 720)
		for i in List[0]:
			s = "The client ID: "
			s += str(i[0].getID()).ljust(10 - len(str(i[0].getID()))) + str(i[0].getName()).ljust(30)
			s += "rented the movie  ID: "
			s += str(i[1].getID()).ljust(10 - len(str(i[1].getID()))) + str(i[1].getTitle()).ljust(70 - len(str(i[1].getTitle())))
			s += "from " + str(i[2].getRentDate()).ljust(30) + " to " + str(i[2].getDueDate()).ljust(12) + " and was "
			if i[2].getReturnDate() == 0:
				s += "not returned yet"
			else:
				s += "returned on " + str(i[2].getReturnDate())
			self._output.insert(END, s)
		self._output.insert(END, "-" * 720)
		if len(List[1]) == 0:
			raise TypeError("No movie currently rented")
		self._output.insert(END, "Currently rented movies:")
		self._output.insert(END, "-" * 720)
		for i in List[1]:
			self._output.insert(END, "  ID: " + str(i.getID()).ljust(10) + str(i.getTitle()).ljust(100))

	def addClient(self):
		self.readParams()
		if len(self._params) != 2:
			self._output.delete(0, END)
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.addClient(self._params)
			self._output.delete(0, END)
			self._output.insert(END, "Succesfully added the client")
		except Exception as ex:
			self._output.delete(0, END)
			self._output.insert(END, ex)

	def addMovie(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 4:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.addMovie(self._params)
			self._output.insert(END, "Succesfully added the movie")
		except Exception as ex:
			self._output.insert(END, ex)

	def readParams(self):
		self._params = self._input.get()
		self._params = self._params.split(',')
		for i in range(len(self._params)):
			self._params[i] = self._params[i].strip()
	
	def undo(self):
		self._output.delete(0, END)
		try:
			self._controller.undo()
			self._output.insert(END, "Succesfully undone the last operation")
		except Exception as ex:
			self._output.insert(END, ex)
	
	def redo(self):
		self._output.delete(0, END)
		try:
			self._controller.redo()
			self._output.insert(END, "Succesfully redone the last undone operation")
		except Exception as ex:
			self._output.insert(END, ex)
	
	def removeClient(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 1:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.removeClient(self._params)
			self._output.insert(END, "Succesfully removed the client")
		except Exception as ex:
			self._output.insert(END, ex)

	def removeMovie(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 1:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.removeMovie(self._params)
			self._output.insert(END, "Succesfully removed the movie")
		except Exception as ex:
			self._output.insert(END, ex)
	
	def updateClient(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 2:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.updateClient(self._params)
			self._output.insert(END, "Succesfully updated the client")
		except Exception as ex:
			self._output.insert(END, ex)
	
	def updateMovie(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 4:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.updateMovie(self._params)
			self._output.insert(END, "Succesfully updated the movie")
		except Exception as ex:
			self._output.insert(END, ex)

	def rent(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 4:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.rent(self._params)
			self._output.insert(END, "Succesfully rented the movie")
		except Exception as ex:
			self._output.insert(END, ex)
	
	def Return(self):
		self.readParams()
		self._output.delete(0, END)
		if len(self._params) != 2:
			self._output.insert(END, "Invalid input")
			return
		try:
			self._controller.Return(self._params)
			self._output.insert(END, "Succesfully returned the movie")
		except Exception as ex:
			self._output.insert(END, ex)

	def showSearch(self):
		self.readParams()
		self._output.delete(0, END)
		try:
			List = self._controller.find(self._params)
			for i in List:
				toShow = str(i).split('\n')
				for j in toShow:
					self._output.insert(END, j.strip())
				self._output.insert(END, "")
		except Exception as ex:
			self._output.insert(END, "No elements found")

	def showLateRentals(self):
		self.readParams()
		self._output.delete(0, END)
		List = self._controller.getLateRentals(self._params)
		if len(List) == 0:
			self._output.insert(END, "No late rentals")
			return
		self._output.insert(END, "The current late rents:")
		self._output.insert(END, "-" * 720)
		for i in List:
			s = "The movie "
			s += "ID: " + str(i[0].getID()).ljust(10 - len(str(i[0].getID())))
			s += str(i[0].getTitle()).ljust(100 - len(str(i[0].getTitle())) // 2)
			s += "passed the due date by    "
			s += str(i[1]).ljust(4)
			s += "days"
			self._output.insert(END, s)


