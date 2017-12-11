from model.operand import operand

class controller():
	
	def addition(self, params):
		"""
		separates the imput from the user interface and returns the result of the called operation
		input: the 2 operands
		output: the result of their addition
		"""
		integer1 = params[1][:]
		integer2 = params[2][:]
		op1 = operand(integer1, params[0])
		op2 = operand(integer2, params[0])
		return (op1 + op2)

	def multiplicationWithOneDigit(self, params):
		"""
		separates the input from the user interface and returns the result of the called operation
		input: the 2 operands
		output: the result of their multiplication
		"""
		integer = params[1][:]
		op = operand(integer, params[0])
		digit = int(params[2])
		return (op * digit)
		
	def divisionWithOneDigit(self, params):
		"""
		separates the input from the user interface and returns the result of the called operation
		input: 1 operand and the digit it will be devided by
		output: the result of their division
		"""
		integer = params[1][:]
		op = operand(integer, params[0])
		digit = int(params[2])
		return (op // digit)

	def substraction(self, params):
		"""
		separates the input from the user interface and returns the result of the called operation
		input: the 2 operands
		output: the result of their substaction
		"""
		integer1 = params[1][:]
		integer2 = params[2][:]
		op1 = operand(integer1, params[0])
		op2 = operand(integer2, params[0])
		return (op1 - op2)

	def succesiveDivisions(self, params):
		"""
		separates the input from the user interface and returns the result of the conversion
		input: the initial base, the operand, the destination base
		output: the converted operand
		"""
		integer = params[1][:]
		desBase = params[2]
		op = operand(integer, params[0])
		return op.succesiveDivisions(desBase)

	def substitutionMethod(self, params):
		"""
		separates the input from the user interface and returns the result of the conversion
		input: the initial base, the operand, the destination base
		output: the converted operand
		"""
		integer = params[1][:]
		desBase = params[2]
		op = operand(integer, params[0])
		return op.substitutionMethod(desBase)
	
	def conversionWithBase10(self, params):
		"""
		separates the input from the user interface and returns the result of the conversion
		input: the initial base, the operand, the destination base
		output: the converted operand
		"""
		integer = params[1][:]
		desBase = params[2]
		op = operand(integer, params[0])
		return op.conversionWithBase10(desBase)
	
	def rapidConversion(self, params):
		"""
		separates the input from the user interface and returns the result of the conversion
		input: the initial base, the operand, the destination base
		output: the converted operand
		"""
		integer = params[1][:]
		desBase = params[2]
		op = operand(integer, params[0])
		return op.rapidConversion(desBase)

