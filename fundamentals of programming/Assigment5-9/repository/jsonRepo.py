from repository.repo import repo
from models.client import client
from models.rental import rental
from models.movie import movie
from datetime import date
import json

class jsonRepo(repo):
	def __init__(self, fileName, instance):
		repo.__init__(self)
		self._instace = instance
		self.readFromFile(fileName)
	
	def readFromFile(self, fileName):
		f = open(fileName, "r")
		s = f.read()
		List = json.loads(s)
		for i in List.keys():
			obj = List[i]
			if self._instace == client:
				cl = client(obj['id'], obj['name'])
				self.addElement(cl)
			elif self._instace == movie:
				mv = movie(obj['id'], obj['title'], obj['description'], obj['genre'])
				self.addElement(mv)
			else:
				rentDate = date(int(obj['rentDate'][:4]), int(obj['rentDate'][5:7]), int(obj['rentDate'][8:]))
				dueDate = date(int(obj['dueDate'][:4]), int(obj['dueDate'][5:7]), int(obj['dueDate'][8:]))
				if obj['returnDate'] == '0':
					rt = rental(obj['movieID'], obj['clientID'], rentDate, dueDate)
				else:
					returnDate = date(int(obj['returnDate'][:4]), int(obj['returnDate'][5:7]), int(obj['returnDate'][8:]))
					rt = rental(obj['movieID'], obj['clientID'], rentDate, dueDate, returnDate)
				self.addElement(rt)
				
	def writeToFile(self, fileName):
		s = {}
		for i in self._list.keys():
			obj = self._list[i]
			if self._instace == client:
				s[obj.getID()] = {"id":obj.getID(), "name":obj.getName()}
			elif self._instace  == movie:
				s[obj.getID()] = {"id":obj.getID(), "title":obj.getTitle(), "description":obj.getDescription(), "genre":obj.getGenre()}
			else:
				s[obj.getID()] = {"clientID":obj.getClientID(), "movieID":obj.getMovieID(), "rentDate":str(obj.getRentDate()), "dueDate":str(obj.getDueDate()), "returnDate":str(obj.getReturnDate())}
			toWrite = json.dumps(s)
			with open(fileName, "w") as f:
				f.write(toWrite)
