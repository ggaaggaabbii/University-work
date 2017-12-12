from models.store import store
from models.rental import rental
from repository.repo import repo
from datetime import date
from controller.undoController import op, functionCall, cascadedOp
from models.list import *

class rentalController:

	def __init__(self, rentalRepo, clientRepo, movieRepo, Store, undoController):
		self._rentalRepo = rentalRepo
		self._clientRepo = clientRepo
		self._movieRepo = movieRepo
		self._store = Store
		self._undoController = undoController
		if self._rentalRepo.getList() != {}:
			rental.setIDCounter(max(self._rentalRepo.getList().keys()))

	def getRepo(self):
		"""
		returns the repository this controller is responsible for
		"""
		return self._rentalRepo

	def validateNr(self, nr):
		"""
		check if a string is built only using digits
		"""
		for i in nr:
			if i < '0' or i > '9':
				raise TypeError("Invalid input!")
	
	def rent(self, params, recordForUndo = True):
		"""
		performs the rent of a movie
		input: the params read from the keyboard
		"""
		IDclient = params[0]
		IDmovie = params[1]
		self.validateNr(IDclient)
		self.validateNr(IDmovie)
		rentDate = self.buildDate(params[2])
		dueDate = self.buildDate(params[3])
		rt = rental(int(IDmovie), int(IDclient), rentDate, dueDate)
		self._store.checkRent(rt, self._clientRepo, self._movieRepo, self._rentalRepo)
		
		redo = functionCall(self._rentalRepo.addElement, rt)
		undo = functionCall(self._rentalRepo.removeElement, rt.getID())
		operation = op(redo, undo)
		self._undoController.recordOperation(operation)
		
		self._rentalRepo.addElement(rt)

	def Return(self, params, recordForUndo = True):
		"""
		performs the return of a movie
		input: the params read from the keyboard
		"""
		IDrent = params[0]
		self.validateNr(IDrent)
		returnDate = self.buildDate(params[1])

		redo = functionCall(self._store.checkReturn, int(IDrent), returnDate, self._rentalRepo)
		undo = functionCall(self._rentalRepo.updateElement, int(IDrent), 0)
		operation = op(redo, undo)
		self._undoController.recordOperation(operation)
		
		self._store.checkReturn(int(IDrent), returnDate, self._rentalRepo)
	
	def buildDate(self, Date):
		"""
		builds a date object from a string(dd/mm/yyyy)
		input: a string of form dd/mm/yyyy
		output: a date object coresponding to the string
		"""
		if len(Date) != 10:
			raise TypeError("Invalid Date!")
		day = Date[:2]
		month = Date[3:5]
		year = Date[6:]
		self.validateNr(day)
		self.validateNr(month)
		self.validateNr(year)
		day = int(day)
		month = int(month)
		year = int(year)
		return date(year, month, day)

	def filterRents(self, clientID, movieID):
		"""
		computes the list of rentals containing the id of a movie or a client
		input: the clientID or the movieID
		output: the result list
		"""
		List = self._rentalRepo.getList()
		if clientID != None:
			def filterFunc(a, IDobj = clientID):
				return a.getClientID() == IDobj
			return Filter(List, filterFunc)
		if movieID != None:
			def filterFunc(a, IDobj = movieID):
				return a.getMovieID() == IDobj
			return Filter(List, filterFunc)

	def getRentedDays(self, clientID, movieID):
		"""
		computes the number of days of a finished rental containing the id of a movie or a client
		input: the movieID or the clientID
		output: the number of days the rental lasted
		"""
		result = 0
		List = self._rentalRepo.getList()
		for i in List.keys():
			if clientID != None and List[i].getClientID() != clientID:
				continue
			if movieID != None and List[i].getMovieID() != movieID:
				continue
			if List[i].getReturnDate() == 0:
				continue
			deltaTime = List[i].getReturnDate() - List[i].getRentDate()
			result += deltaTime.days
		return result

	def listRents(self, params):
		"""
		outputs the list of rentals
		"""
		return self._rentalRepo.getList()

	def mostRentedMovie(self):
		"""
		computes the list of movies sorted by 2 different methods-the number of times it was rented and the amount of days it was rented for
		output: a pair of the 2 result lists
		"""
		mostRentedByNumberOfRents = []
		mostRentedByNumberOfDays = []
		movies = self._movieRepo.getList()
		for i in movies.keys():
			mostRentedByNumberOfRents.append([movies[i], len(self.filterRents(None, movies[i].getID()))])
			mostRentedByNumberOfDays.append([movies[i], self.getRentedDays(None, movies[i].getID())])
		sort(mostRentedByNumberOfRents, compareSecondFieldReverse)
		sort(mostRentedByNumberOfDays, compareSecondFieldReverse)
		return (mostRentedByNumberOfRents, mostRentedByNumberOfDays)

	def mostActiveClient(self):
		"""
		computes the list of most active clients by the number of rented days
		output: the result list
		"""
		mostActiveClients = []
		clients = self._clientRepo.getList()
		for i in clients.keys():
			mostActiveClients.append([clients[i], self.getRentedDays(clients[i].getID(), None)])
		sort(mostActiveClients, compareSecondFieldReverse)
		return mostActiveClients
		
	def allRentals(self):
		"""
		returns the list of all current rentals
		output: the result list
		"""
		allRentals = []
		rentedMovies = []
		rentals = self._rentalRepo.getList()
		for i in rentals.keys():
			allRentals.append([self._clientRepo.getByID(rentals[i].getClientID()), self._movieRepo.getByID(rentals[i].getMovieID()), rentals[i]])
			if rentals[i].getReturnDate() == 0:
				rentedMovies.append(self._movieRepo.getByID(rentals[i].getMovieID()))

		return (allRentals, rentedMovies)

	def lateRentals(self, params):
		"""
		returns the late rentals at a given date
		input: the date
		output: the result list
		"""
		Date = self.buildDate(params[0])
		lateRents = []
		rents = self._rentalRepo.getList()
		for i in rents.keys():
			if rents[i].getReturnDate() == 0 and rents[i].getDueDate() < Date:
				lateRents.append([self._movieRepo.getByID(rents[i].getMovieID()), (Date - rents[i].getDueDate()).days])
		sort(lateRents, compareSecondFieldReverse)
		return lateRents
	
def compareSecondFieldReverse(a, b):
	return a[1] > b[1]
