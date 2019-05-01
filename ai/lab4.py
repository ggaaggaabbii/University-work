import math

class GraphClass():
	"""docstring for GraphClass"""
	def __init__(self, a, b, c, d):
		self.__a = a
		self.__b = b
		self.__c = c
		self.__d = d

	def __str__(self):
		return "[" + str(self.__a) + ", " + str(self.__b) + ", " + str(self.__c) + ", " + str(self.__d) +"]"

	def membership(self, x):
		val1 = math.inf
		if self.__b - self.__a != 0:
			val1 = (x - self.__a) / (self.__b - self.__a)
		val2 = math.inf
		if self.__d - self.__c != 0:
			val2 = (self.__d - x) / (self.__d - self.__c)
		return max(0, min(val1, val2, 1))


class Controller(object):
	"""docstring for Controller"""
	def __init__(self):
		self.__textures = []
		self.__capacities = []
		self.__cycleTypes = []
		self.__table = []

		self.loadData()
		print(list(map(lambda x: str(x), self.__textures)))
		print(list(map(lambda x: str(x), self.__capacities)))
		print(list(map(lambda x: str(x), self.__cycleTypes)))
		print(self.__table)

	def loadData(self):
		#read the capacities
		with open("capacity") as f:
			while True:
				line = f.readline()
				if line == "":
					break

				line = line.split()
				self.__capacities.append(GraphClass(float(line[0]), 
													float(line[1]),
													float(line[2]),
													float(line[3])))
		#read the textures
		with open("texture") as f:
			while True:
				line = f.readline()
				if line == "":
					break

				line = line.split()
				self.__textures.append(GraphClass(float(line[0]), 
												  float(line[1]),
												  float(line[2]),
												  float(line[3])))
		#read the cycle types
		with open("cycle_type") as f:
			while True:
				line = f.readline()
				if line == "":
					break

				line = line.split()
				self.__cycleTypes.append(GraphClass(float(line[0]), 
													float(line[1]),
													float(line[2]),
													float(line[3])))

		#read table
		with open("table") as f:
			i = 0
			while True:
				line = f.readline()
				if line == "":
					break

				self.__table.append([])
				line = line.split()
				for j in line:
					self.__table[i].append(int(j))

				i += 1

	def membership(self, cls, x):
		return cls.membership(x) 

	def evaluate(self, texture, capacity):
		memberships1 = []
		memberships2 = []
		resultTable = []
		coeficients = []

		for i in range(len(self.__textures)):
			memberships1.append(self.membership(self.__textures[i], texture))

		for i in range(len(self.__capacities)):
			memberships2.append(self.membership(self.__capacities[i], capacity))
		
		print(memberships1, memberships2)

		for i in range(len(self.__cycleTypes)):
			coeficients.append(0)

		for i in range(len(memberships1)):
			resultTable.append([])
			for j in range(len(memberships2)):
				resultTable[i].append(min(memberships1[i], memberships2[j]))
				if coeficients[self.__table[i][j]] < resultTable[i][j]:
					coeficients[self.__table[i][j]] = resultTable[i][j]

		print("result table:")
		print(resultTable)
		print("coeficients:")
		print(coeficients)

		"""
		mamdani:
		mamdani is adefuzzing method that calculates the centroid of area
		using a simulation of an integral on the entire set of values
		it uses the distributions of probabilities
		on the aggregationed output of the fuzzing method
		"""
		upSum = 0
		downSum = 0
		i = 0
		while i <= 1.0:
			for j in range(len(coeficients)):
				upSum += i * coeficients[j] * self.membership(self.__cycleTypes[j], i)
				downSum += coeficients[j] * self.membership(self.__cycleTypes[j], i)
			i += 0.1

		if downSum == 0:
			print("Invalid input")
		else:
			return upSum / downSum
		
class UI(object):
	"""docstring for UI"""
	def __init__(self, controller):
		self.__ctrl = controller


	def run(self):
		while True:
			texture = float(input("texture: "))
			capacity = float(input("capacity: "))
			print(self.__ctrl.evaluate(texture, capacity))



if __name__ == "__main__":
	c = Controller()
	u = UI(c)
	u.run()

		