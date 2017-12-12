from repository.repo import repo
from models.client import client
from models.movie import movie
from models.rental import rental
import sqlite3
from datetime import date

class SQLrepo(repo):
	def __init__(self, database, table, instance):
		repo.__init__(self)
		self._connection = sqlite3.connect(database)
		self._cursor = self._connection.cursor()
		self._instance = instance
		self._table = table
		if self._instance == client:
			self._cursor.execute('CREATE TABLE IF NOT EXISTS clients(id NUMERIC, name TEXT)')
		elif self._instance == movie:
			self._cursor.execute('CREATE TABLE IF NOT EXISTS movies(id NUMERIC, title TEXT, description TEXT, genre TEXT)')
		else:
			self._cursor.execute('CREATE TABLE IF NOT EXISTS rentals(clientID NUMERIC, movieID NUMERIC, rentDate TEXT, dueDate TEXT, returnDate TEXT)')
		
		if self._instance == client:
			self._cursor.execute('SELECT * FROM clients')
		elif self._instance == movie:
			self._cursor.execute('SELECT * FROM movies')
		else:
			self._cursor.execute('SELECT * FROM rentals')
		self._data = self._cursor.fetchall()
		self.buildList()


	def buildList(self):
		for i in self._data:
			if self._instance == client:
				self.addElement(client(i[0], i[1]))
			elif self._instance == movie:
				self.addElement(movie(i[0], i[1], i[2], i[3]))
			else:
				rentDate = date(int(i[2][:4]), int(i[2][5:7]), int(i[2][8:]))
				dueDate = date(int(i[3][:4]), int(i[3][5:7]), int(i[3][8:]))
				if i[4] == '0':
					rt = rental(i[1], i[0], rentDate, dueDate)
				else:
					returnDate = date(int(i[4][:4]), int(i[4][5:7]), int(i[4][8:]))
					rt = rental(i[1], i[0], rentDate, dueDate, returnDate)
				self.addElement(rt)
				
	def writeToFile(self, a):
		if self._instance == client:
			self._cursor.execute('DELETE FROM clients')
			for i in self._list.keys():
				j = self._list[i]
				self._cursor.execute('INSERT INTO clients (id, name) VALUES(?, ?)', (j.getID(), j.getName()))
		elif self._instance == movie:
			self._cursor.execute('DELETE FROM movies')
			for i in self._list.keys():
				j = self._list[i]
				self._cursor.execute('INSERT INTO movies (id, title, description, genre) VALUES(?, ?, ?, ?)', (j.getID(), j.getTitle(), j.getDescription(), j.getGenre()))
		else:
			self._cursor.execute('DELETE FROM rentals')
			for i in self._list.keys():
				j = self._list[i]
				self._cursor.execute('INSERT INTO rentals (clientID, movieID, rentDate, dueDate, returnDate) VALUES(?, ?, ?, ?, ?)', (j.getClientID(), j.getMovieID(), str(j.getRentDate()), str(j.getDueDate()), str(j.getReturnDate())))
		self._connection.commit()
