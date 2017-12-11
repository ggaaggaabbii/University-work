class operand:
	"""
	values dictionaries
	"""
	values = {"0" : 0, "1" : 1, "2" : 2, "3" : 3, "4" : 4, "5" : 5, "6" : 6, "7" : 7, "8" : 8, "9" : 9, 
						"A" : 10, "B" : 11, "C" : 12, "D" : 13, "E" : 14, "F" : 15}
	strings = {0 : "0", 1 : "1", 2 : "2", 3 : "3", 4 : "4", 5 : "5", 6 : "6", 7 : "7", 8 : "8", 9 : "9",
						10 : "A", 11 : "B", 12 : "C", 13 : "D", 14 : "E", 15 : "F"}
	log = {2 : 1, 4 : 2, 8 : 3, 16 : 4}

	def __init__(self, integer, base):
		"""
		initialize the operand with the integer part, the fractional part and the base it is written into
		"""
		self._integer = integer
		self._base = base

	def __str__(self):
		"""
		form the string which will be displayed
		"""
		s = ""
		for i in range(len(self._integer)):
			if self._integer[i] != "0":
				s += self._integer[i:]
				break
		if s == "":
			s = "0"
		return s

	def __add__(self, other):
		"""
		performs the addition of 2 operands
		input: 2 operands
		output: the result of their addition
		"""
		integer = ""
		carry = 0
		"""
		adds the integer parts
		"""
		indexSelf = len(self._integer) - 1
		indexOther = len(other._integer) - 1
		for i in range(max(indexSelf, indexOther), -1, -1):
			if indexOther < 0:
				res = operand.values[self._integer[indexSelf]] + carry
				carry = res // self._base
				res -= carry * self._base
				integer = operand.strings[res] + integer
				indexSelf -= 1
			elif indexSelf < 0:
				res = operand.values[other._integer[indexOther]] + carry
				carry = res // self._base
				res -= carry * self._base
				integer = operand.strings[res] + integer
				indexOther -= 1
			else:
				res = operand.values[self._integer[indexSelf]] + operand.values[other._integer[indexOther]] + carry
				carry = res // self._base
				res -= carry * self._base
				integer = operand.strings[res] + integer
				indexSelf -= 1
				indexOther -= 1
		"""
		adds the extra digit if it is necessary
		"""
		if carry > 0:
			integer = operand.strings[carry] + integer
		"""
		returns the result as an operand
		"""
		return operand(integer, self._base)

	def __mul__(self, digit):
		"""
		performs the multiplication of 1 operand with a 1-digit number
		input: 1 operand, 1 digit
		output: the result of their multiplication
		"""
		carry = 0
		integer = ""
		for i in range(len(self._integer) - 1, -1, -1):
			res = operand.values[self._integer[i]] * digit + carry
			carry = res // self._base
			res -= carry * self._base
			integer = operand.strings[res] + integer

		if carry > 0:
			integer = operand.strings[carry] + integer

		return operand(integer, self._base)
	
	def __sub__(self, other):
		"""
		performs the substaction of 2 operands
		input: 2 operands
		output: the result of their substraction
		"""
		carry = 0
		integer = ""
		for i in range(len(self._integer) - len(other._integer)):
			other._integer = "0" + other._integer
		for i in range(len(self._integer) - 1, -1, -1):
			res = operand.values[self._integer[i]] - operand.values[other._integer[i]] - carry
			if res < 0:
				carry = 1
				res += operand.values[operand.strings[self._base - 1]] + 1
			else:
				carry = 0
			integer = operand.strings[res] + integer
		return operand(integer, self._base)

	def __floordiv__(self, digit):
		"""
		performs the division of an operand with a 1-digit number
		input: the operand and the digit
		output: a list of the quotient and the remainder
		"""
		carry = 0
		currentDiv = 0
		integer = ""
		for i in range(len(self._integer)):
			currentDiv = currentDiv * self._base + operand.values[self._integer[i]]
			carry = currentDiv % digit
			integer += operand.strings[(currentDiv - carry) / digit]
			currentDiv = carry
		return (operand(integer, self._base), operand(operand.strings[carry], self._base))

	def succesiveDivisions(self, destBase):
		"""
		performs the conversion using the succesive divisions method
		input: the operand, the destination base
		ouput: the result operand after conversion
		"""
		integer = ""
		aux = self
		while True:
			res = aux // destBase#devide the current number by the destination base
			integer = res[1]._integer + integer#add the remainder to the result value
			aux = res[0]#take the result of the division and repeat the algorithm
			if str(aux) == "0":
				return operand(integer, destBase)
			
	def substitutionMethod(self, destBase):
		"""
		performs the conversion using the substitution method
		input: the operand, the destination base
		output: the result operand after conversion
		"""
		result = operand("0", destBase)
		power = operand("1", destBase)
		for i in range(len(self._integer) - 1, -1, -1):
			result = result + power * int(self._integer[i])
			power = power * self._base
		return result
	

	def conversionWithBase10(self, destBase):
		"""
		performs the conversion using 10 as a intermediar base
		input: the operand, the destination base
		output: the result operand after conversion
		"""
		if self._base < 10:
			self = self.substitutionMethod(10)
		else:
			self = self.succesiveDivisions(10)

		if self._base < destBase:
			self = self.substitutionMethod(destBase)
		else:
			self = self.succesiveDivisions(destBase)
		return self

	def rapidConversion(self, destBase):
		"""
		performs the conversion using the rapid conversion method
		input: the operand, the destination base
		output: the result operand after conversion
		"""
		resultInteger = ""
		currentInteger = ""
		for i in range(len(self._integer) - 1, -1, -1):
			op = operand(self._integer[i], self._base).succesiveDivisions(2)._integer
			currentInteger = op + currentInteger
			while len(currentInteger) % operand.log[self._base] != 0:
				currentInteger = "0" + currentInteger

		while len(currentInteger) % operand.log[destBase] != 0:
			currentInteger = "0" + currentInteger
		
		index = len(currentInteger)
		while index > 0:
			resultInteger = operand(currentInteger[index - operand.log[destBase] : index], 2).substitutionMethod(destBase)._integer + resultInteger
			index -= operand.log[destBase]

		return operand(resultInteger, destBase)
					
