class finder():
	def __init__(self, clientRepo, movieRepo):
		self._clientRepo = clientRepo
		self._movieRepo = movieRepo

	def find(self, string):
		"""
		computes the list of objects that contain a given string in one of their components
		input: the given string
		output: the result list
		raise: error if no elements contain the string
		"""
		List = []
		string = string.lower()
		for i in self._clientRepo.getList().keys():
			s = self._clientRepo.getList()[i].getSearchStr()
			s = s.lower()
			if string in s:
				List.append(self._clientRepo.getList()[i])
		for i in self._movieRepo.getList().keys():
			s = self._movieRepo.getList()[i].getSearchStr()
			s = s.lower()
			if string in s:
				List.append(self._movieRepo.getList()[i])

		if len(List) == 0:
			raise ValueError("No elements found")
		return List
