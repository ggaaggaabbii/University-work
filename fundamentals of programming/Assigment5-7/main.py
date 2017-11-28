from ui.ui import UI
from controller.controller import controller
from models.store import store
from repository.repo import repo
from models.finder import finder
from controller.clientController import clientController
from controller.movieController import movieController
from controller.rentalController import rentalController
from controller.removalController import removalController
from controller.undoController import undoController
import pickle

def readFromFile(File):
	"""
	reads the contains of a file
	input: the file name
	output: its contains
	"""
	f = open(File, "rb")
	return pickle.load(f)

def main():
	
	clRepo = readFromFile("clientRepo.pickle")
	mvRepo = readFromFile("movieRepo.pickle")
	rtRepo = readFromFile("rentalRepo.pickle")
	st = store()
	find = finder(clRepo, mvRepo)
	undoC = undoController()
	clc = clientController(clRepo, undoC)
	mvc = movieController(mvRepo, undoC)
	rtc = rentalController(rtRepo, clRepo, mvRepo, st, undoC)
	rmc = removalController(clRepo, mvRepo, rtRepo, undoC, rtc)
	CL = controller(clc, mvc, rtc, rmc, undoC, find)
	u = UI(CL)
	u.start()

main()
