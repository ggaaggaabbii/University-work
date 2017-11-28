from models.client import client
from repository.repo import repo
from copy import deepcopy
from controller.undoController import op, functionCall, cascadedOp
from controller.rentalController import rentalController

class removalController:
	def __init__(self, clientRepo, movieRepo, rentalRepo, undoController, rentalController):
		self._clientRepo = clientRepo
		self._movieRepo = movieRepo
		self._rentalRepo = rentalRepo
		self._undoController = undoController
		self._rentalController = rentalController
	
	def removeClient(self, params, recordForUndo = True):
		"""
		removes a client by ID and the rentals associated with it
		input: the params read from the keyboard
		raise: error if there are missing parameters
		"""
		if params == "" or len(params[0]) == 0:
			raise TypeError("Missing parameters!")
		ID = params[0]
		self.validateNr(ID)
		
		redo = functionCall(self._clientRepo.removeElement, int(ID))
		cl = self._clientRepo.getByID(int(ID))
		undo = functionCall(self._clientRepo.addElement, cl)
		operation = op(redo, undo)
		cascadedOperation = cascadedOp(operation)
		
		self._clientRepo.removeElement(int(ID))
		rents = self._rentalRepo.getList().keys()
		toDelete = []
		for i in rents:
			if self._rentalRepo.getList()[i].getClientID() == int(ID):
				toDelete.append(i)
		for i in toDelete:
			
			rt = self._rentalRepo.getByID(i)
			undo = functionCall(self._rentalRepo.addElement, rt)
			redo = functionCall(self._rentalRepo.removeElement, i)
			operation = op(redo, undo)
			cascadedOperation.add(operation)
			
			self._rentalRepo.removeElement(i)
		
		self._undoController.recordOperation(cascadedOperation)


	def removeMovie(self, params, recordForUndo = True):
		"""
		removes a movie by ID and the rentals associated with it
		input: the params read from the keyboard
		raise: error if there are missing parameters
		"""
		if params == "" or len(params[0]) == 0:
			raise TypeError("Missing parameters!")
		ID = params[0]
		self.validateNr(ID)
		
		redo = functionCall(self._movieRepo.removeElement, int(ID))
		mv = self._movieRepo.getByID(int(ID))
		undo = functionCall(self._movieRepo.addElement, mv)
		operation = op(redo, undo)
		cascadedOperation = cascadedOp(operation)
		
		self._movieRepo.removeElement(int(ID))
		rents = self._rentalRepo.getList().keys()
		toDelete = []
		for i in rents:
			if self._rentalRepo.getList()[i].getMovieID() == int(ID):
				toDelete.append(i)
		for i in toDelete:

			rt = self._rentalRepo.getByID(i)
			undo = functionCall(self._rentalRepo.addElement, rt)
			redo = functionCall(self._rentalRepo.removeElement, i)
			operation = op(redo, undo)
			cascadedOperation.add(operation)
			
			self._rentalRepo.removeElement(i)
			
		self._undoController.recordOperation(cascadedOperation)

	def validateNr(self, nr):
		"""
		check if a string is built only using digits
		input: a string
		raise: error if there are non-digit characters in the string
		"""
		for i in nr:
			if i < '0' or i > '9':
				raise TypeError("Invalid input!")
	

