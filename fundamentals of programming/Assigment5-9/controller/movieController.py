from models.movie import movie
from repository.repo import repo
from controller.undoController import op, functionCall, cascadedOp

class movieController:
	
	def __init__(self, movieRepo, undoController):
		self._movieRepo = movieRepo
		self._undoController = undoController

	def getRepo(self):
		"""
		returns the repository this controller is responsible for
		"""
		return self._movieRepo

	def addMovie(self, params, recordForUndo = True):
		"""
		adds a new movie to the store
		"""
		if params == "" or len(params) < 3:
			raise TypeError("Missing parameters!")
		ID = params[0]
		name = params[1]
		description = params[2]
		genre = params[3]
		self.validateNr(ID)
		mv = movie(int(ID), name, description, genre)
		self._movieRepo.addElement(mv)
		if recordForUndo == False:
			return
		undo = functionCall(self._movieRepo.removeElement, int(ID))
		redo = functionCall(self.addMovie, [ID, name, description, genre], False)
		operation = op(redo, undo)
		self._undoController.recordOperation(operation)

	def listMovies(self):
		"""
		lists the movies to the console
		"""
		return self._movieRepo.getList()

	def updateMovie(self, params, recordForUndo = True):
		"""
		updates the title of a movie with a given ID
		input: the params read from the keyboard
		raise: error if there are missing parameters
		"""
		if params == "" or len(params) < 2:
			raise TypeError("Missing parameters!")
	
		ID = params[0]
		title = params[1]
		description = params[2]
		genre = params[3]
		self.validateNr(ID)
		if recordForUndo == True:
			mv = self._movieRepo.getByID(int(ID))
			undo = functionCall(self.updateMovie, [str(mv.getID()), mv.getTitle(), mv.getDescription(), mv.getGenre()], False)
			redo = functionCall(self.updateMovie, [ID, title, description, genre], False)
			operation = op(redo, undo)
			self._undoController.recordOperation(operation)
		self._movieRepo.updateElement(int(ID), movie(int(ID), title, description, genre))

	def validateNr(self, nr):
		"""
		check if a string is built only using digits
		input: a string
		raise: error if the string has non-digit characters
		"""
		for i in nr:
			if i < '0' or i > '9':
				raise TypeError("Invalid input!")
	
