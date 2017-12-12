from ui.ui import UI
from ui.gui import GUI
from controller.controller import controller
from models.store import store
from repository.repo import repo
from repository.binaryRepo import binaryRepo
from repository.fileRepo import fileRepo
from repository.jsonRepo import jsonRepo
from repository.SQLrepo import SQLrepo
from models.finder import finder
from models.client import client
from models.movie import movie
from models.rental import rental
from controller.clientController import clientController
from controller.movieController import movieController
from controller.rentalController import rentalController
from controller.removalController import removalController
from controller.undoController import undoController
import pickle
from configparser import ConfigParser

class Settings:
	def __init__(self, fileName):
		self._cfg = ConfigParser()
		self._cfg.read(fileName)
		try:
			self._userInterface = self._cfg.get('config', 'ui')
		except Exception:
			self._userInterface = 'console'
		self._repository = self._cfg.get('config', 'repository')
		if self._repository == 'inmemory':
			self._clRepo = repo()
			self._mvRepo = repo()
			self._rtRepo = repo()
		elif self._repository == 'binaryfiles':
			self._clRepo = binaryRepo(self._cfg.get('config', 'clients'))
			self._mvRepo = binaryRepo(self._cfg.get('config', 'movies'))
			self._rtRepo = binaryRepo(self._cfg.get('config', 'rentals'))
		elif self._repository == 'jsonfiles':
			self._clRepo = jsonRepo(self._cfg.get('config', 'clients'), client)
			self._mvRepo = jsonRepo(self._cfg.get('config', 'movies'), movie)
			self._rtRepo = jsonRepo(self._cfg.get('config', 'rentals'), rental)
		elif self._repository == "sql":
			self._clRepo = SQLrepo('data.db', 'clients', client)
			self._mvRepo = SQLrepo('data.db', 'movies', movie)
			self._rtRepo = SQLrepo('data.db', 'rentals', rental)
		else:
			self._clRepo = fileRepo(self._cfg.get('config', 'clients'), client)
			self._mvRepo = fileRepo(self._cfg.get('config', 'movies'), movie)
			self._rtRepo = fileRepo(self._cfg.get('config', 'rentals'), rental)
		
		self._st = store()
		self._find = finder(self._clRepo, self._mvRepo)
		self._undoC = undoController()
		self._clc = clientController(self._clRepo, self._undoC)
		self._mvc = movieController(self._mvRepo, self._undoC)
		self._rtc = rentalController(self._rtRepo, self._clRepo, self._mvRepo, self._st, self._undoC)
		self._rmc = removalController(self._clRepo, self._mvRepo, self._rtRepo, self._st, self._undoC)
		self._CL = controller(self._clc, self._mvc, self._rtc, self._rmc, self._undoC, self._find)
		if self._userInterface == 'gui':
			self._ui = GUI(self._CL)
		else:
			self._ui = UI(self._CL)
	

	def startUi(self):
		self._ui.start()
		
	def saveData(self):
		if self._repository != 'inmemory':
			self._clRepo.writeToFile(self._cfg.get('config', 'clients'))
			self._mvRepo.writeToFile(self._cfg.get('config', 'movies'))
			self._rtRepo.writeToFile(self._cfg.get('config', 'rentals'))


if __name__ == '__main__':
	setup = Settings('settings.properties')
	setup.startUi()
	setup.saveData()

