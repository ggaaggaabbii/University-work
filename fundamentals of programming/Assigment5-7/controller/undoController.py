class undoController:

	def __init__(self):
		self.history = []
		self._index = -1
	
	def recordOperation(self, cascadedOperation):
		"""
		adds an operation to the history of operations
		input: a cascaded operation
		"""
		if len(self.history) != 0:
			self.history = self.history[:self._index + 1]
		self.history.append(cascadedOperation)
		self._index += 1

	def undo(self):
		"""
		performs the undo of the current operation from the history
		raise: error if there is no current operation to be undone
		"""
		if self._index == -1:
			raise ValueError("Already the latest version")
		operation = self.history[self._index]
		operation.undo()
		self._index -= 1

	def redo(self):
		"""
		performs the redo of the current operation from the history
		raise: error if there is no current operation to be redone
		"""
		if self._index == len(self.history) - 1:
			raise ValueError("Already the newest version")
		self._index += 1
		operation = self.history[self._index]
		operation.redo()

class functionCall:
	def __init__(self, function, *params):
		self._function = function
		self._params = params
	def call(self):
		self._function(*self._params)

class op:
	def __init__(self, functionDo, functionUndo):
		self._functionDo = functionDo
		self._functionUndo = functionUndo
	
	def undo(self):
		self._functionUndo.call()
	
	def redo(self):
		self._functionDo.call()

class cascadedOp:
	def __init__(self, operation = None):
		self._operations = []
		if operation != None:
			self.add(operation)
	
	def add(self, operation):
		self._operations.append(operation)
	
	def undo(self):
		for i in range(len(self._operations) - 1, -1, -1):
			self._operations[i].undo()
	
	def redo(self):
		for i in range(len(self._operations) - 1, -1, -1):
			self._operations[i].redo()
