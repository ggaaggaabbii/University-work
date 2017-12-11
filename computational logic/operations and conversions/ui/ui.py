from controller.controller import controller

class UI():

	allowedBases = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
	values = {"0" : 0, "1" : 1, "2" : 2, "3" : 3, "4" : 4, "5" : 5, "6" : 6, "7" : 7, "8" : 8, "9" : 9, 
						"A" : 10, "B" : 11, "C" : 12, "D" : 13, "E" : 14, "F" : 15}
	mul2 = [2, 4, 8, 16]

	def __init__(self, controller):
		self._controller = controller

	def printMenu(self):
		print("Menu:")
		print("\t0. Exit")
		print("\t1. Addition")
		print("\t2. Substraction")
		print("\t3. Multiplication with 1 digit")
		print("\t4. Division with 1 digit")
		print("\t5. Convert")

	def readCommand(self, c):
		if c == "0":
			pass
		if c == "1":
			self.readAdditionParams()
		if c == "2":
			self.readSubstractionParams()
		if c == "3":
			self.readMultiplicationParams()
		if c == "4":
			self.readMultiplicationParams()
		if c == "5":
			self.readConversionParams()

	def start(self):

		while True:
			try:
				self.printMenu()
				c = input()
				self.readCommand(c)
				if c == "0":
					print("Exiting...")
					break
				elif c == "1":
					print(self._controller.addition(self._params))
				elif c == "2":
					print(self._controller.substraction(self._params))
				elif c == "3":
					print(self._controller.multiplicationWithOneDigit(self._params))
				elif c == "4":
					result = self._controller.divisionWithOneDigit(self._params)
					print(str(result[0]) + ", remainder " + str(result[1]))
				elif c == "5":
					print(self.callConversion())
				else:
					print("Invalid Command!")
			except Exception as ex:
				print(ex)
		

	def validateNr(self, nr):
		for i in nr:
			if i < "0" or i > "9":
				raise ValueError("Base must be an integer!")

	def validateBase(self, operand, base):
		counter = 0
		for i in operand:
			if i not in UI.values.keys() or UI.values[i] >= base:
				raise ValueError("Invalid Operand!")

	def readAdditionParams(self):
		base = input("Introduce the base: ")
		self.validateNr(base)
		base = int(base)
		if base not in UI.allowedBases:
			raise ValueError("Invalid Base!")
		self._params = []
		self._params.append(base)
		self._params.append(input("Introduce the first operand: "))
		self._params.append(input("Introduce the second operand: "))
		self.validateBase(self._params[1], self._params[0])
		self.validateBase(self._params[2], self._params[0])

	def readSubstractionParams(self):
		base = input("Introduce the base: ")
		self.validateNr(base)
		base = int(base)
		if base not in UI.allowedBases:
			raise ValueError("Invalid, Base!")
		self._params = []
		self._params.append(base)
		self._params.append(input("Introduce the first operand: "))
		self._params.append(input("Introduce the second operand: "))
		self.validateBase(self._params[1], self._params[0])
		self.validateBase(self._params[2], self._params[0])
		if len(self._params[2]) > len(self._params[1]):
			raise ValueError("Can't perform the operation")
		if len(self._params[2]) == len(self._params[1]) and self._params[2][0] > self._params[1][0]:
			raise ValueError("Can't perform the operation")

	def readMultiplicationParams(self):
		base = input("Introduce the base: ")
		self.validateNr(base)
		base = int(base)
		if base not in UI.allowedBases:
			raise ValueError("Invalid Base!")
		self._params = []
		self._params.append(base)
		self._params.append(input("Introduce the first operand: "))
		self._params.append(input("Introduce the second operand: "))
		self.validateBase(self._params[1], self._params[0])
		self.validateBase(self._params[2], self._params[0])
		if len(self._params[2]) != 1:
			raise ValueError("The second operand must be 1 digit")
		else:
			self._params[2] = UI.values[self._params[2]]

	def readConversionParams(self):
		base = input("Introduce the source base: ")
		self.validateNr(base)
		base = int(base)
		if base not in UI.allowedBases:
			raise ValueError("Invalid Base!")
		self._params = []
		self._params.append(base)
		self._params.append(input("Introduce the number: "))
		self.validateBase(self._params[1], self._params[0])
		base = input("Introduce the destination base: ")
		self.validateNr(base)
		base = int(base)
		if base not in UI.allowedBases:
			raise ValueError("Invalid base!")
		self._params.append(base)


	def callConversion(self):
		"""
		print(self._controller.conversionWithBase10(self._params))
		"""
		if self._params[0] in UI.mul2 and self._params[2] in UI.mul2:
			return self._controller.rapidConversion(self._params)
		if self._params[0] > self._params[2]:
			return self._controller.succesiveDivisions(self._params)
		else:
			return self._controller.substitutionMethod(self._params)
		
		

