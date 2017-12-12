from repository.repo import repo
import pickle
from models.client import client
from models.movie import movie
from models.rental import rental
import json


class binaryRepo(repo):
	def __init__(self, fileName):
		repo.__init__(self)
		self.readFromFile(fileName)
	
	def readFromFile(self, fileName):
		f = open(fileName, "rb")
		self._list = pickle.load(f)._list

	def writeToFile(self, fileName):
		f = open(fileName, "wb")
		pickle.dump(self, f)
		f.close()
