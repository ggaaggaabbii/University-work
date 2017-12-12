from models.client import client
from models.rental import rental
from models.movie import movie

class store:

	def checkRent(self, rent, clientRepo, movieRepo, rentRepo):
		"""
		checks if a rental is valid
		input: the rental itself, the client, movie and rent repositories
		raise: error if the rental is not valid
		"""
		if rent.getClientID() not in clientRepo.getList().keys():
			raise ValueError("Invalid Client ID")
		if rent.getMovieID() not in movieRepo.getList().keys():
			raise ValueError("Invalid Movie ID")

		for i in rentRepo.getList().keys():
			if rentRepo.getList()[i].getClientID() == rent.getClientID():
				if rentRepo.getList()[i].getDueDate() < rent.getRentDate() and rentRepo.getList()[i].getReturnDate() == 0:
					raise TypeError("Client has a unreturned movie!")
			if rentRepo.getList()[i].getMovieID() == rent.getMovieID():
				if rentRepo.getList()[i].getReturnDate() == 0:
					raise TypeError("Movie unavailable!")
				if rentRepo.getList()[i].getReturnDate() != 0 and rent.getRentDate() < rentRepo.getList()[i].getReturnDate():
					raise TypeError("Movie unavailable!")

	def checkReturn(self, rentID, returnDate, rentRepo):
		"""
		cheks if the return is valid and updates the return date of a ended rental
		input: the rental ID, the return date and the rent repository
		raise: error if the return can not be performed
		"""
		for i in rentRepo.getList().keys():
			if rentRepo.getList()[i].getID() == rentID:
				if rentRepo.getList()[i].getReturnDate() == 0 and rentRepo.getList()[i].getRentDate() < returnDate:
					rentRepo.getList()[i].updateReturnDate(returnDate)
				else:
					raise ValueError("The movie can't be returned")
				return

		raise ValueError("The rental ID is invalid!")
