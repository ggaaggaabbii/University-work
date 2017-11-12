from math import gcd

class UI:
	def __init__(self, fun):
		self.fun = fun
	
	def menu(self):
		while True:
			print("1. Print list")
			print("2. Add number")
			print("3. Exit")
			cmd = int(input("Enter an option"))
			if cmd == 1:
				for i in self.fun.getAll():
					print(str(i))
			elif cmd == 2:
				num = int(input("Enter numinator"))
				nom = int(input("Enter nominator"))
				try:
					self.fun.add(Rational(num, nom))
				except ValueError:
					print("Nominator must not be 0")
			elif cmd == 3:
				break
			else:
				print("Invalid option")

class Functions:
	def __init__(self):
		self.list = []
	
	def add(self, nr):
		self.list.append(nr)
	
	def getAll(self):
		return self.list

class Rational:
	def __init__(self, num, nom = 1):
		self.num = num
		self.nom = nom
		if self.nom == 0:
			raise ValueError("Nominator must not be 0")
		self.simplify()
	
	def __str__(self):
		if self.nom == 1:
			return str(self.num)
		return str(self.num) + " / " + str(self.nom)
	
	def simplify(self):
		a = gcd(self.num, self.nom)
		self.num = self.num // a
		self.nom = self.nom // a

def testRational():
	assert str(Rational(1, 2)) == "1 / 2"
	assert str(Rational(10, 20)) == "1 / 2"
	assert str(Rational(2, 1)) == "2"
	assert str(Rational(-3, 4)) == "-3 / 4"
	assert str(Rational(2)) == "2"
	assert str(Rational(0, 3)) == "0"
	try:
		Rational(5, 0)
		assert False
	except ValueError:
		assert True

def testFunctions():
	f = Functions()
	x = Rational(1, 2)
	y = Rational(2, 3)
	assert f.getAll() == []
	f.add(x)
	f.add(y)
	assert f.getAll() == [x, y]

f = Functions()
f.add(Rational(10, 20))
f.add(Rational(-3, 4))
u = UI(f)
UI.menu(u)
"""
functia a(){}
functia b({};
functia c({};
functia d({};
"""
