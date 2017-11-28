import unittest
import sys
sys.path.append('./..')
from models.client import client
from models.movie import movie
from models.store import store
from models.rental import rental
from controller.controller import controller
from controller.movieController import movieController
from controller.clientController import clientController
from controller.rentalController import rentalController
from controller.removalController import removalController
from controller.undoController import undoController
from datetime import date
from repository.repo import repo
from models.finder import finder
import coverage

class tester(unittest.TestCase):

	def testMovieObject(self):
		mv = movie(1, "Titanic", "cel mai bun", "Comedy")
		self.assertEqual(mv.getTitle(), "Titanic")
		self.assertEqual(mv.getDescription(), "cel mai bun")
		self.assertEqual (mv.getGenre(), "Comedy")
		mv.updateTitle("Fight Club")
		self.assertEqual (mv.getTitle(), "Fight Club")
		mv.updateDescription("smecher")
		self.assertEqual (mv.getDescription(), "smecher")
		mv.updateGenre("Action")
		mv.getGenre() == "Action"
		mv.updateID(2)
		a = str(mv)
		a = mv.getSearchStr()
		with self.assertRaises(Exception):
			mv.updateGenre("drama")
		with self.assertRaises(Exception):
			mv = movie(1,"Titanic", "creative movie", "drama")
		with self.assertRaises(Exception):
			mv = movie(1)

	def testClientObject(self):
		cl = client(1, "Pop Mircea")
		self.assertEqual (cl.getID(), 1)
		self.assertEqual (cl.getName(),  "Pop Mircea")
		cl.updateName("Mircea Pop")
		a = str(cl)
		a = cl.getSearchStr()
		self.assertEqual (cl.getName(), "Mircea Pop")
		with self.assertRaises(Exception):
			cl = client(name = "Pop Mircea")
	
		with self.assertRaises(Exception):
			cl = client()

		with self.assertRaises(Exception):
			cl = client(1, "A1212")

		with self.assertRaises(Exception):
			cl = client(1, "Pop mircea")

		with self.assertRaises(Exception):
			cl = client(1, "pop Mircea")

	def testRepo(self):
		movRep = repo()
		with self.assertRaises(Exception):
			movRep.listElements()
		movRep.addElement(movie(1, "Titanic", "Nice", "Romance"))
		movRep.addElement(movie(2, "Avatar", "Good movie", "Sci-Fi"))
		movRep.addElement(movie(3, "The Matrix", "WoW", "Action"))
		movRep.addElement(movie(4, "The Wizard of Oz", "Excelent!", "Adventure"))
		movRep.addElement(movie(5, "Star Wars", "Exceptional!", "Sci-Fi"))

		with self.assertRaises(Exception):
			movRep.addElement(movie(2, "d", "d", "Romance"))
		movRep.removeElement(2)
		with self.assertRaises(Exception):
			movRep.removeElement(2)

		movRep.updateElement(3, movie(3, "The Matrix", "wow", "Sci-Fi"))
		self.assertEqual(movRep.getList()[3], movie(3, "The Matrix", "wow", "Sci-Fi"))

		with self.assertRaises(Exception):
			movRep.updateElement(2, movie(3, "The Matrix", "wow", "Sci-Fi"))

		with self.assertRaises(Exception):
			a = movRep.getByID(2)


	def testRentObject(self):
		mv = movie(1, "Titanic", "Nice", "Romance")
		cl = client(1, "Poo Mircea")
		rent = rental(1, 1, date(2017, 11, 11), date(2017, 11, 13))
		self.assertEqual(rent.getID(), rental.ID)
		self.assertEqual(rent.getMovieID(), 1)
		self.assertEqual(rent.getClientID(), 1)
		self.assertEqual(rent.getRentDate(), date(2017, 11, 11))
		self.assertEqual(rent.getDueDate(), date(2017, 11, 13))
		self.assertEqual(rent.getReturnDate(), 0)
		a = str(rent)
		rent.updateReturnDate(date(2017, 11, 14))
		self.assertEqual(rent.getReturnDate(), date(2017, 11, 14))
		a = str(rent)
		with self.assertRaises(Exception):
			a = rental(1, 1, date(2017, 11, 11), date(2017, 11, 10))
	
	def testFunctional(self):
		rental.resetIDCounter()
		mvRepo = repo()
		clRepo = repo()
		rtRepo = repo()
		st = store()
		find = finder(clRepo, mvRepo)
		undoC = undoController()
		clc = clientController(clRepo, undoC)
		mvc = movieController(mvRepo, undoC)
		rtc = rentalController(rtRepo, clRepo, mvRepo, st, undoC)
		rmc = removalController(clRepo, mvRepo, rtRepo, undoC, rtc)
		CL = controller(clc, mvc, rtc, rmc, undoC, find)
		with self.assertRaises(Exception):
			a = CL.find("1")
		CL.addClient(["1", "Pop Vasile"])
		with self.assertRaises(Exception):
			CL.removeMovie(["ds"])
		CL.addMovie(["1", "Titanic", "nice", "Drama"])
		a = CL.listMovies()
		a = CL.listClients()
		a = CL.listRents("")
		CL.rent(["1", "1", "11/11/2017", "13/11/2017"])
		with self.assertRaises(Exception):
			CL.rent(["1", "1", "11/11/21", "12"])
		with self.assertRaises(Exception):
			CL.rent(["1", "1", "10/11/2017", "11/11/2017"])
		with self.assertRaises(Exception):
			CL.rent(["1", "1", "12/11/2017", "14/11/2017"])
		a = CL.getAllRentals()
		CL.addClient(["10", "Laur"])
		a = str(CL.getAllRentals()[0][0])
		CL.addMovie(["2", "Titanic2", "d", "Drama"])
		with self.assertRaises(Exception):
			CL.rent(["1", "2", "15/11/2017", "16/11/2017"])
		CL.rent(["10", "2", "13/11/2017", "14/11/2017"])
		CL.removeMovie(["2"])
		CL.Return(["1", "14/11/2017"])
		CL.rent(["10", "1", "17/11/2017", "19/11/2017"])
		with self.assertRaises(Exception):
			CL.Return(["1", "13/11/2017"])
		with self.assertRaises(Exception):
			CL.Return(["10", "11/11/2017"])
		with self.assertRaises(Exception):
			CL.rent(["10", "1", "13/11/2017", "16/11/2017"])
		self.assertEqual(str(CL.find("Pop")[0]), str(client("1", "Pop Vasile")))
		CL.addClient(["3", "Ion"])
		CL.addMovie(["2", "Titanic2", "Nice", "Drama"])
		a = CL.getAllRentals()
		a = CL.getLateRentals(["13/11/2017"])
		a = CL.getMostActive()
		a = CL.getMostRented()
		a = CL.find("1")
		CL.updateClient(["1", "Pop Viorel"])
		CL.updateMovie(["1", "Titanic2", "nice", "Sci-Fi"])
		CL.addClient(["2", "Ion"])
		CL.removeClient(["1"])
		CL.removeMovie(["1"])
		with self.assertRaises(Exception):
			CL.addMovie("")
		with self.assertRaises(Exception):
			CL.removeMovie("")
		with self.assertRaises(Exception):
			CL.updateMovie("")
		with self.assertRaises(Exception):
			CL.addMovie(["c", "Titanic", "nice", "Romance"])
		with self.assertRaises(Exception):
			CL.removeClient("")
		with self.assertRaises(Exception):
			CL.addClient("")
		with self.assertRaises(Exception):
			CL.updateClient("")
		with self.assertRaises(Exception):
			CL.addClient(["c", "Viorel"])
		with self.assertRaises(Exception):
			CL.rent(["2", "1", "11/11/2017", "11/11/2017"])
		CL.removeClient(["2"])
		with self.assertRaises(Exception):
			CL.rent(["3", "1", "11/11/2017", "13/11/2017"])
		with self.assertRaises(Exception):
			CL.rent(["4", "1", "11/11/2017", "13/11/2017"])
		a = CL._clientController.getRepo()
		a = CL._movieController.getRepo()
		a = CL._rentalController.getRepo()


	def testFunctional2(self):
		rental.resetIDCounter()
		rental.setIDCounter(0)
		mvRepo = repo()
		clRepo = repo()
		rtRepo = repo()
		st = store()
		find = finder(clRepo, mvRepo)
		undoC = undoController()
		clc = clientController(clRepo, undoC)
		mvc = movieController(mvRepo, undoC)
		rtc = rentalController(rtRepo, clRepo, mvRepo, st, undoC)
		rmc = removalController(clRepo, mvRepo, rtRepo, undoC, rtc)
		CL = controller(clc, mvc, rtc, rmc, undoC, find)
		with self.assertRaises(Exception):
			CL.undo()
		with self.assertRaises(Exception):
			CL.redo()
		CL.addClient(["1", "Pop Ion"])
		CL.undo()
		CL.redo()
		CL.addMovie(["1", "Titanic", "nice", "Drama"])
		CL.undo()
		CL.redo()
		CL.rent(["1", "1", "11/11/2017", "14/11/2017"])
		CL.removeMovie(["1"])
		CL.undo()
		CL.redo()
		CL.undo()
		CL.removeClient(["1"])
		CL.undo()
		CL.redo()
		CL.undo()
		CL.updateClient(["1", "Pop Viorel"])
		CL.undo()
		CL.redo()
		CL.updateMovie(["1", "Titanic2", "nice", "Drama"])
		CL.undo()
		CL.redo()
		a = CL.getLateRentals(["15/11/2017"])
		CL.Return(["1", "16/11/2017"])
		CL.undo()
		CL.redo()
		CL.addClient(["2", "Ion Ion"])
		CL.addMovie(["2", "Avatar", "nice", "Sci-Fi"])
		CL.rent(["2", "2", "14/11/2017", "15/11/2017"])
		with self.assertRaises(Exception):
			CL.Return(["a", "11/11/2017"])
		a = CL.getMostActive()
		a = CL.getMostRented()
		CL.writeToFile()


if __name__ == '__main__':
	cov = coverage.Coverage(branch = True, include = './../*')
	cov.start()
	tests = unittest.TestLoader().discover('.')
	unittest.TextTestRunner(verbosity = 2).run(tests)
	cov.stop()
	cov.save()
	print ("Coverage Summary:")
	cov.report()
	cov.html_report()
	
