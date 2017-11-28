from models.finder import finder
from controller.clientController import clientController
from controller.movieController import movieController
from controller.removalController import removalController
from controller.undoController import undoController
import pickle

class controller:
	def __init__(self, clientController, movieController, rentalController, removalController, undoController, finder):
		"""
		initiates the store
		"""
		self._clientController = clientController
		self._movieController = movieController
		self._rentalController = rentalController
		self._removalController = removalController
		self._undoController = undoController
		self._finder = finder

	def addClient(self, params):
		"""
		calls the addClient function in the client controller
		"""
		self._clientController.addClient(params)

	def addMovie(self, params):
		"""
		calls the addMovie function in the movie controller
		"""
		self._movieController.addMovie(params)

	def listClients(self):
		"""
		calls the listClient function in the client controller
		"""
		return self._clientController.listClients()
	
	def listMovies(self):
		"""
		calls the listMovie function in the movie controller
		"""
		return self._movieController.listMovies()
	
	def removeClient(self, params):
		"""
		calls the removeClient function in the client controller
		"""	
		self._removalController.removeClient(params)
	
	def removeMovie(self, params):
		"""
		calls the removeMovie function in the movie controller
		"""
		self._removalController.removeMovie(params)
	
	def updateClient(self, params):
		"""
		calls the updateClient function in the client controller
		"""
		self._clientController.updateClient(params)
	
	def updateMovie(self, params):
		"""
		calls the updateMovie function in the movie controller
		"""
		self._movieController.updateMovie(params)
	
	def rent(self, params):
		"""
		calls the rent function in the rental controller
		"""
		self._rentalController.rent(params)
	
	def Return(self, params):
		"""
		calls the Return function in the rental controller
		"""
		self._rentalController.Return(params)

	def listRents(self, params):
		"""
		calls the list function in the rental controller
		"""
		return self._rentalController.listRents(params)

	def getMostRented(self):
		"""
		outputs the most rented movies
		"""
		return self._rentalController.mostRentedMovie()

	def getMostActive(self):
		"""
		outputs the most active clients
		"""
		return self._rentalController.mostActiveClient()

	def getAllRentals(self):
		"""
		outputs all the rentals and the currently rented movies
		"""
		return self._rentalController.allRentals()

	def getLateRentals(self, params):
		"""
		outputs the list of late rentals at a given date
		"""
		return self._rentalController.lateRentals(params)

	def find(self, params):
		"""
		outputs the result of a search command
		"""
		string = params[0]
		return(self._finder.find(string))
	
	def undo(self):
		"""
		performs the undo operation
		"""
		self._undoController.undo()
	
	def redo(self):
		"""
		performs the redo operation
		"""
		self._undoController.redo()

	def writeToFile(self):
		"""
		writes the current repositories to binary files
		"""
		f = open("clientRepo.pickle", "wb")
		pickle.dump(self._clientController.getRepo(), f)
		f.close()
		f = open("movieRepo.pickle", "wb")
		pickle.dump(self._movieController.getRepo(), f)
		f.close()
		f = open("rentalRepo.pickle", "wb")
		pickle.dump(self._rentalController.getRepo(), f)
		f.close()
		
