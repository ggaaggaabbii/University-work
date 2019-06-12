import random
import math

depth = 5
functions = ["xd", "*", "+", "-"]
noFunctions = 3
terminals = ["mizerie", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9"]
noTerminals = 9

class Individ(object):
	"""docstring for Individ"""
	def __init__(self):
		self.values = [0 for i in range(2 ** depth)]
		for i in range(len(self.values)):
			if i < 3 or (i < 2 ** (depth - 1) - 1 and random.random() < 0.5):
				self.values[i] = -random.randint(1, len(functions) - 1)
			else:
				self.values[i] = random.randint(1, len(terminals) - 1)


	def fitness(self, problem):
		s = 0
		for i in range(len(problem.inData)):
			rez = self.dfs(0, problem.inData[i])
			s += (rez - problem.outData[i]) * (rez - problem.outData[i])
			#print("Expected:", problem.outData[i], "Got: ", rez)
		return 100000.0 / s

	def eval(self, problem):
		s = 0
		for i in range(len(problem.inData)):
			rez = self.dfs(0, problem.inData[i])
			s += (rez - problem.outData[i]) * (rez - problem.outData[i])
			print("Expected:", problem.outData[i], "Got: ", rez)
		return 100000.0 / s

	def dfs(self, pos, inputs):
		if (self.values[pos] > 0):
			return inputs[self.values[pos] - 1]

		if (functions[-self.values[pos]] == "*"):
			return self.dfs(2 * pos + 1, inputs) * self.dfs(2 * pos + 2, inputs)

		if (functions[-self.values[pos]] == "-"):
			return self.dfs(2 * pos + 1, inputs) - self.dfs(2 * pos + 2, inputs)

		if (functions[-self.values[pos]] == "+"):
			return self.dfs(2 * pos + 1, inputs) + self.dfs(2 * pos + 2, inputs)


	def mutate(self, probability):
		index1 = random.randint(0, (2 ** (depth - 1)) - 2)
		index2 = random.randint(0, (2 ** (depth - 1)) - 2)

		i = min(index1, index2)
		j = max(index1, index2)

		while i < j:
			self.values[i], self.values[j] = self.values[j], self.values[i]
			i += 1
			j -= 1


	def crossover(individ1, individ2, probability):
		offspring1 = Individ()
		offspring2 = Individ()

		index1 = random.randint(0, (2 ** (depth)))
		index2 = random.randint(0, (2 ** (depth)))

		i = min(index1, index2)
		j = max(index1, index2)

		for k in range(0, (2 ** (depth))):
			if k in range(i, j):
				offspring1.values[k] = individ1.values[k]
				offspring2.values[k] = individ2.values[k]
			else:
				offspring1.values[k] = individ2.values[k]
				offspring2.values[k] = individ1.values[k]

		return offspring1, offspring2

	def __str__(self):
		return str(self.values)



class Algorithm(object):
	"""docstring for Algorithm"""
	def __init__(self, problem, populationSize = 40):
		self.__problem = problem
		self.readParameters()
		self.__populationSize = populationSize
		self.__population = Population(self.__populationSize)

	def getPopulation(self):
		return self.__population

	def iteration(self):
		self.__population.selection(self.__problem)
		self.__population.evaluate(self.__problem)

	def run(self):
		for i in range(100):
			self.iteration()
			print(
				self.__population.getBest(), 
				self.__population.getBest().fitness(self.__problem),
				self.__population.getPopSize()
			)
		self.__population.getBest().eval(self.__problem)

	def readParameters(self):
		self.__problem.loadData("slump_test.data")
		
class Population(object):
	"""docstring for Population"""
	def __init__(self, noIndivids):
		self.__noIndivids = noIndivids
		self.__individs = []
		for i in range(noIndivids):
			self.__individs.append(Individ())

	def evaluate(self, problem):
		for i in range(self.__noIndivids // 2 - 1):
			offspring1, offspring2 = Individ.crossover(self.__individs[i], self.__individs[i + 1], 0.5)
			self.__individs.append(offspring1)
			self.__individs.append(offspring2)

		offspring1, offspring2 = Individ.crossover(self.__individs[self.__noIndivids // 2 - 1], self.__individs[0], 0.5)
		self.__individs.append(offspring1)
		self.__individs.append(offspring2)

		for i in range(self.__noIndivids):
			self.__individs[i].mutate(0.08)
		self.__individs.sort(key = lambda x : x.fitness(problem), reverse = True)

	def getBest(self):
		return self.__individs[0]

	def getPopSize(self):
		return len(self.__individs)

	def selection(self, problem):
		s = 0
		newPopulation = []

		for i in range(self.__noIndivids):
			s += self.__individs[i].fitness(problem)

		for i in range(self.__noIndivids // 2):
			r = random.random()
			j = 0
			percents = 0
			while j < self.__noIndivids and percents < r:
				percents += self.__individs[j].fitness(problem) / s
				j += 1
			j -= 1
			newPopulation.append(self.__individs[j])
			s -= self.__individs[j].fitness(problem)
			self.__individs.pop(j)
		self.__individs = newPopulation


	def __str__(self):
		s = ""
		for i in self.__individs:
			s += str(i) + "\n"
		return s


class Problem(object):
	"""docstring for Problem"""
	def __init__(self):
		self.inData = []
		self.outData = []


	def loadData(self, fileName):
		with open(fileName, "r") as f:
			while True:
				line = f.readline()
				if (line == ""):
					break
				line = line.split(",")
				crtIn = []
				for i in range(1, 10):
					crtIn.append(float(line[i].strip()))
				self.outData.append(float(line[10].strip()))
				self.inData.append(crtIn) 

	
if __name__ == "__main__":
	p = Problem()
	a = Algorithm(p, 40)
	a.run()





