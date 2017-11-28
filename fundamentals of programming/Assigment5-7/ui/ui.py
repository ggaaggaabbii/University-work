from controller.controller import controller
import pickle

class UI:
	def __init__(self, controller):
		self._controller = controller
	
	def printMenu(self):
		"""
		prints the menu to the console
		"""
		print("Menu:")
		print("\taddclient <name>")
		print("\taddmovie <title>, <description>, <genre>")
		print("\tremoveclient <id>")
		print("\tremovemovie <id>")
		print("\tupdateclient <id>, <name>")
		print("\tupdatemovie <id>, <title>, <description>, <genre>")
		print("\tlistclients")
		print("\tlistmovies")
		print("\tlistrents")
		print("\trent <clintID>, <movieID>, <rentDate(dd/mm/yyyy)>, <dueDate(dd/mm/yyyy)>")
		print("\treturn <rentID>, <returnDate(dd/mm/yyyy)>")
		print("\tsearch <filter>")
		print("\tmostrented")
		print("\tmostactive")
		print("\trentals")
		print("\tlate <date(dd/mm/yyyy)>")
		print("\tundo")
		print("\tredo")
		
		

	def readCommand(self):
		"""
		reads a command from the keyboard
		"""
		command = input("command: ")
		if command.find(" ") == -1:
			self._cmd = command
			self._params = ""
		else:
			self._cmd = command[:command.find(" ")]
			self._params = command[command.find(" "):]
			self._params = self._params.strip()
			self._params = self._params.split(",")
			for i in range(len(self._params)):
				self._params[i] = self._params[i].strip()

	def printSearch(self, List):
		for i in List:
			print(i)

	def printMostRented(self, List):
		if len(List[0]) == 0:
			raise TypeError("The list is empty")
		print("The most rented movies are:")
		print("-" * 160)
		for i in List[0]:
			print("\tID: " + str(i[0].getID()).ljust(4) + str(i[0].getTitle()).ljust(40) + " rented " + str(i[1]).ljust(5) + " times")
		print("-" * 160)
		for i in List[1]:
			print("\tID: " + str(i[0].getID()).ljust(4) + str(i[0].getTitle()).ljust(40) + " rented for " + str(i[1]).ljust(5) + " days")

	def printMostActive(self, List):
		if len(List) == 0:
			raise TypeError("The list is empty")
		print("The most active clients are: ")
		print("-" * 160)
		for i in List:
			print("\tID: " + str(i[0].getID()).ljust(4) + str(i[0].getName()).ljust(25) + " rented movies for " + str(i[1]).ljust(5) + " days")

	def printRentals(self, List):
		if len(List[0]) == 0:
			raise TypeError("No rentals")
		print("The rentals are:")
		print("-" * 160)
		for i in List[0]:
			s = "The client ID: "
			s += str(i[0].getID()).ljust(4) + str(i[0].getName()).ljust(18)
			s += "rented the movie  ID: "
			s += str(i[1].getID()).ljust(4) + str(i[1].getTitle()).ljust(30)
			s += "from " + str(i[2].getRentDate()).ljust(12) + " to " + str(i[2].getDueDate()).ljust(12) + " and was "
			if i[2].getReturnDate() == 0:
				s += "not returned yet"
			else:
				s += "returned on " + str(i[2].getReturnDate())
			print(s)
		print("-" * 160)
		if len(List[1]) == 0:
			raise TypeError("No movie currently rented")
		print("Currently rented movies:")
		print("-" * 160)
		for i in List[1]:
			print("\tID: " + str(i.getID()).ljust(4) + str(i.getTitle()).ljust(40))

	def printLate(self, List):
		if len(List) == 0:
			raise TypeError("No late rents at the time")
		print("The current late rents:")
		print("-" * 160)
		for i in List:
			s = "The movie "
			s += "ID: " + str(i[0].getID()).ljust(4)
			s += str(i[0].getTitle()).ljust(35)
			s += "passed the due date by\t"
			s += str(i[1]).ljust(4)
			s += "days"
			print(s)


	def listElements(self, List):
		"""
		prints the contains of a list to the screen
		input: the list
		raise: error if the list is empty
		"""
		if len(List.keys()) == 0:
			raise ValueError("List is empty!")
		for i in List.keys():
			print(List[i])

	def writeToFile(self):
		f = open("data.pickle", "wb")
		pickle.dump(self._controller, f)
		f.close()

	

	def start(self):
		"""
		starts the ui method
		"""
		print("enter the \"help\" command to see the menu")
		while True:
			try:
				self.readCommand()
				self.checkParams()
				if self._cmd == "addclient":
					self._controller.addClient(self._params)
				elif self._cmd == "exit":
					break
				elif self._cmd == "listclients":
					self.listElements(self._controller.listClients())
				elif self._cmd == "help":
					self.printMenu()
				elif self._cmd == "addmovie":
					self._controller.addMovie(self._params)
				elif self._cmd == "listmovies":
					self.listElements(self._controller.listMovies())
				elif self._cmd == "removeclient":
					self._controller.removeClient(self._params)
				elif self._cmd == "updatemovie":
					self._controller.updateMovie(self._params)
				elif self._cmd == "updateclient":
					self._controller.updateClient(self._params)
				elif self._cmd == "removemovie":
					self._controller.removeMovie(self._params)
				elif self._cmd == "rent":
					self._controller.rent(self._params)
				elif self._cmd == "return":
					self._controller.Return(self._params)
				elif self._cmd == "listrents":
					self.listElements(self._controller.listRents(self._params))
				elif self._cmd == "search":
					self.printSearch(self._controller.find(self._params))
				elif self._cmd == "mostrented":
					self.printMostRented(self._controller.getMostRented())
				elif self._cmd == "mostactive":
					self.printMostActive(self._controller.getMostActive())
				elif self._cmd == "rentals":
					self.printRentals(self._controller.getAllRentals())
				elif self._cmd == "late":
					self.printLate(self._controller.getLateRentals(self._params))
				elif self._cmd == "undo":
					self._controller.undo()
				elif self._cmd == "redo":
					self._controller.redo()
				else:
					print("Invalid command!")
			except Exception as ex:
				print (ex)
			
		self.writeToFile()
		self._controller.writeToFile()

	def checkParams(self):
		"""
		checks if a command is asociated with the right number of parameters
		"""
		if self._cmd == "listclients" and self._params != "":
			raise TypeError("Invalid numbers of parameters!")
		if self._cmd == "listmovies" and self._params != "":
			raise TypeError("Invalid numbers of parameters!")
		if self._cmd == "addmovie" and len(self._params) != 4:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "addclient" and len(self._params) != 2:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "removemovie" and len(self._params) != 1:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "removeclient" and len(self._params) != 1:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "updatemovie" and len(self._params) != 4:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "updateclient" and len(self._params) != 2:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "help" and self._params != "":
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "exit" and self._params != "":
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "rent" and len(self._params) != 4:
			raise TypeError("Invalid Command!")
		if self._cmd == "return" and len(self._params) != 2:
			raise TypeError("Invalid Command!")
		if self._cmd == "listrents" and self._params != "":
			raise TypeError("Invalid Command!")
		if self._cmd == "search" and len(self._params) != 1:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "mostrented" and self._params != "":
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "mostactive" and self._params != "":
			raise TypeError("Invalid number or parameters!")
		if self._cmd == "rentals" and self._params != "":
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "late" and len(self._params) != 1:
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "undo" and self._params != "":
			raise TypeError("Invalid number of parameters!")
		if self._cmd == "redo" and self._params != "":
			raise TypeError("Invalid number of parameters!")

	
