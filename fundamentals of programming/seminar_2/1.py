def addStudent(sList, Student):
	if checkId(sList, Student[0]):
		sList.append(Student)
		return True
	return False

def checkId(sList, Id):
	for i in range (0, len(sList)):
		if sList[i][0] == Id:
			return False
	return True

def readStudent():
	Id = input("give the student's id: ")
	name = input("give the student's name: ")
	grade = int(input("give the student's grade: "))
	return (Id, name, grade)

def deleteStudent(sList):
	Id = input("give the id ")
	for i in range(0, len(sList)):
		if sList[i][0] == Id:
			sList[i], sList[len(sList) - 1] = sList[len(sList) - 1], sList[i]
			sList.pop(len(sList) - 1)
			return
	print("there is no student with this id")
			
def printMenu():
	print("0.end the program")
	print("1.add a student")
	print("2.delete a student by id")
	print("3.show the students")
	print("4.show the student with a grade greater tha a given number")

def showStudents(sList):
	for i in sList:
		print (i)

def filterStudents(sList):
	Filter = int(input("give a grade: "))
	ok = 0
	for i in sList:
		if i[2] >= Filter:
			print (i)
			ok = 1
	if ok == 0:
		print ("no student meet the requirement")

def start():
	sList = []
	while True:
		printMenu()
		a = input()
		if a == "1":
			Student = readStudent()
			if addStudent(sList, Student):
				print("Student added succesfully")
			else:
				print("error while adding student")
		elif a == "0":
			break
		elif a == "2":
			deleteStudent(sList)
		elif a == "3":
			showStudents(sList)
		elif a == "4":
			filterStudents(sList)
		else:
			print("Error")

start()
