from models.client import client
from repository.repo import repo
from controller.undoController import op, functionCall, cascadedOp

class clientController:
	def __init__(self, clientRepo, undoController):
		self._clientRepo = clientRepo
		self._undoController = undoController
	
	def getRepo(self):
		"""
		returns the repository this controller is responsible for
		"""
		return self._clientRepo

	def addClient(self, params, recordForUndo = True):
		"""
		builds a client from the parameters given
		input: the parameters read from the keyboard
		raise: error if there are missing parameters
		"""
		if params == "":
			raise TypeError("Missing parameters!")
		ID = params[0]
		name = params[1]
		self.validateNr(ID)
		cl = client(int(ID), name)
		self._clientRepo.addElement(cl)
		if recordForUndo == False:
			return
		undo = functionCall(self._clientRepo.removeElement, int(ID))
		redo = functionCall(self.addClient, [ID, name], False)
		operation = op(redo, undo)
		self._undoController.recordOperation(operation)

	def listClients(self):
		"""
		lists the clients to the console
		"""
		return self._clientRepo.getList()
		
	def updateClient(self, params, recordForUndo = True):

		"""
		updates the name of a client with a given ID
		input: the params read from the keyboard
		raise: error if there are missing parameters
		"""
		if params == "" or len(params) < 2:
			raise TypeError("Missing parameters!")
		ID = params[0]
		name = params[1]
		self.validateNr(ID)
		if recordForUndo == True:
			cl = self._clientRepo.getByID(int(ID))
			undo = functionCall(self.updateClient, [str(cl.getID()), cl.getName()], False)
			redo = functionCall(self.updateClient, [ID, name], False)
			operation = op(redo, undo)
			self._undoController.recordOperation(operation)
		self._clientRepo.updateElement(int(ID), client(int(ID), name))

	def validateNr(self, nr):
		"""
		check if a string is built only using digits
		input: a string
		raise: error if there are non-digit characters in the string
		"""
		for i in nr:
			if i < '0' or i > '9':
				raise TypeError("Invalid input!")
	

