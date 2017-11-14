from controller.controller import *
from tester.tester import *

def printMenu():
	"""
	prints the menu
	"""
	print("Menu")
	print("\t0. Exit")
	print("\t1. Add Flight")
	print("\t2. Print Flights")
	print("\t3. Remove Flight")
	print("\t4. List Sorted")
	print("\t5. Increment duration")

def validateNr(number):
	"""
	checks if a string is composed only with digits
	"""
	for i in number:
		if i < "0" or i > "9":
			return False
	return True

def readSortedParams():
	depCity = input("Introduce the departure city: ")
	return depCity

def readAddParams():
	"""
	reads from the keyboard the details of a flight
	"""
	code = input("Introduce the flight code: ")
	duration = input("Introduce the flight duration: ")
	if validateNr(duration) == False:
		raise TypeError("Duration must be an int!")
	duration = int(duration)
	depCity = input("Introduce the departure city: ")
	desCity = input("Introduce the destination city: ")
	return [code, duration, depCity, desCity]

def readRemoveParams():
	"""
	reads from the keyboard the code of the flight
	"""
	code = input("Introduce the flight code: ")
	return code

def printList(fList):
	for i in fList:
		print(i)

def readIncrementParams():
	depCity = input("Introduce the departure city: ")
	duration = input("Introduce the duration: ")
	if validateNr(duration) == False:
		raise TypeError("Duration must be an int!")
	duration = int(duration)
	return [depCity, duration]

def start():
	"""
	starts the main application, initializes the list, takes the command from the user and calls the according function in controller
	"""
	fList = testInit()
	while True:
		try:
			printMenu()
			c = input()
			if c == "1":
				if addFlight(fList, readAddParams()) == True:
					print("Succesfully added the flight")
			elif c == "2":
				printFlights(fList)
			elif c == "3":
				if deleteFlight(fList, readRemoveParams()) == True:
					print("Succesfully removed the flight")
			elif c == "4":
				printList(listSorted(fList, readSortedParams()))
			elif c == "5":
				if incrementDuration(fList, readIncrementParams()) == True:
					print("Succesfully incremented the duration")
			elif c == "0":
				print("Exiting...")
				break
		except Exception as ex:
			print(ex)
			
