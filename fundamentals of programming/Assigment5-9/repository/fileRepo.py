from repository.repo import repo
from models.client import client
from models.movie import movie
from models.rental import rental
from datetime import date

class fileRepo(repo):
	def __init__(self, fileName, instance):
		repo.__init__(self)
		self._instance = instance
		self.readFromFile(fileName)

	def readFromFile(self, fileName):
		f = open(fileName, "r")
		n = int(f.readline().strip())
		for i in range(n):
			new = f.readline().strip()
			new = new.split(',')
			if self._instance == client:
				self.addElement(client(int(new[0]), new[1]))
			elif self._instance == movie:
				self.addElement(movie(int(new[0]), new[1], new[2], new[3]))
			else:
				if new[5] == "0":
					rt = rental(int(new[2]), int(new[1]), self.buildDate(new[3]), self.buildDate(new[4]))
				else:
					rt = rental(int(new[2]), int(new[1]), self.buildDate(new[3]), self.buildDate(new[4]), self.buildDate(new[5]))
				self.addElement(rt)

	def buildStr(self, Date):
		if Date == 0:
			return "0"
		s = ""
		if Date.day < 10:
			s += "0"
		s += str(Date.day)
		s += "/"
		if Date.month < 10:
			s += "0"
		s += str(Date.month)
		s += "/"
		return s + str(Date.year)


	def buildDate(self, Date):
		"""
		builds a date object from a string(dd/mm/yyyy)
		input: a string of form dd/mm/yyyy
		output: a date object coresponding to the string
		"""
		day = Date[:2]
		month = Date[3:5]
		year = Date[6:]
		day = int(day)
		month = int(month)
		year = int(year)
		return date(year, month, day)

	def writeToFile(self, fileName):
		f = open(fileName, "w")
		f.write(str(len(self._list.keys())) + "\n")
		for i in self._list.keys():
			if self._instance == client:
				f.write(str(self._list[i].getID()) + "," + self._list[i].getName() + "\n")
			elif self._instance == movie:
				f.write(str(self._list[i].getID()) + "," + self._list[i].getTitle() + ',')
				f.write(self._list[i].getDescription() + "," + self._list[i].getGenre() + "\n")
			else:
				f.write(str(self._list[i].getID()) + "," + str(self._list[i].getClientID()) + "," + str(self._list[i].getMovieID()) + ",")
				f.write(self.buildStr(self._list[i].getRentDate()) + "," + self.buildStr(self._list[i].getDueDate()) + ",")
				f.write(self.buildStr(self._list[i].getReturnDate()) + "\n")
		f.close()
