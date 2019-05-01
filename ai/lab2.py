import random
import math
import numpy as np
import matplotlib.pyplot as plt

def getBitArrayForInt(n):
	l = []
	while n > 0:
		l.append(n % 2)
		n //= 2
	return l

def getIntForBitArray(l):
	nr = 0
	p = 1
	for i in l:
		nr += i * p
		p *= 2
	if nr > 23:
		nr = nr % 24
	return nr

class Individ(object):
	"""docstring for Individ"""
	def __init__(self, size):
		self.__size = size
		self.__x = []
		for i in range(size):
			self.__x.append(random.randint(0, 23))

	def setX(self, x):
		self.__x = x

	def getX(self):
		return self.__x

	def fitness(self, problem):
		s = 0
		#print("new call")
		for i in range(self.__size - 1):
			#print(self.__x)
			downFaceCurrent = self.__x[i] // 4 + 1
			downFaceNext = self.__x[i + 1] // 4 + 1
			neighboursCurrent = problem.getNeighbours(downFaceCurrent)
			neighboursNext = problem.getNeighbours(downFaceNext)

			#print(neighboursCurrent, neighboursNext)

			for j in range(self.__x[i] % 4):
				neighboursCurrent.append(neighboursCurrent[0])
				neighboursCurrent.pop(0)

			for j in range(self.__x[i + 1] % 4):
				neighboursNext.append(neighboursNext[0])
				neighboursNext.pop(0)

			data = problem.getData()
			data1 = data[i]
			data2 = data[i + 1]

			#print(data1, data2, neighboursCurrent, neighboursNext)
			c = 0
			for j in range(4):
				if data1[neighboursCurrent[j]] == data2[neighboursNext[j]]:
					c += 1

			if c != 0 and c % 4 == 0:
				s += 6
			s += c

		return s * s


	def mutate(self, probability):
		if random.random() < probability:
			self.__x[random.randint(0, self.__size - 1)] = random.randint(0, 23)

	def crossover(individ1, individ2, probability):
		x1 = individ1.getX()
		x2 = individ2.getX()
		offspring1 = Individ(len(x1))
		offspring2 = Individ(len(x2))

		newX1 = []
		newX2 = []
		for i in range(len(x1)):
			l1 = getBitArrayForInt(x1[i])
			l2 = getBitArrayForInt(x2[i])
			l3 = []
			l4 = []

			for j in range(min(len(l1), len(l2))):
				if random.random() < 0.5:
					l3.append(l1[j])
				else:
					l3.append(l2[j])
				if random.random() < 0.5:
					l4.append(l1[j])
				else:
					l4.append(l2[j])


			for j in range(min(len(l1), len(l2)), len(l1)):
				l3.append(l1[j])
				l4.append(l1[j])

			for j in range(min(len(l1), len(l2)), len(l2)):
				l3.append(l2[j])
				l4.append(l2[j])

			newX1.append(getIntForBitArray(l3))
			newX2.append(getIntForBitArray(l4))

		offspring1.setX(newX1)
		offspring2.setX(newX2)
		return offspring1, offspring2

	def __str__(self):
		l = []
		for i in range(self.__size):
			l.append(str(self.__x[i] // 4 + 1) + " down, " + str(self.__x[i] % 4) + " turns")

		return str(l)


class Algorithm(object):
	"""docstring for Algorithm"""
	def __init__(self, problem, populationSize):
		self.__problem = problem
		self.readParameters()
		self.__populationSize = populationSize
		self.__population = Population(self.__populationSize, self.__problem.getSize())
		self.__time = []
		self.__means = []
		self.__diviations = []

	def getPopulation(self):
		return self.__population

	def statistics(self):
		return self.__population.getMean(self.__problem), self.__population.getStandardDiviation(self.__problem)

	def iteration(self):
		self.__population.selection(self.__problem)
		self.__population.evaluate(self.__problem)

	def run(self):
		i = 0
		
		for i in range(100):
			self.iteration()
			stats = self.statistics()
			self.__time.append(i)
			self.__means.append(stats[0])
			self.__diviations.append(stats[1])
			i += 1
			print(
				self.__population.getBest(), 
				self.__population.getBest().fitness(self.__problem),
				self.statistics(),
				self.__population.getPopSize()
			)

		fig, ax = plt.subplots()
		x = np.array(self.__time)
		y = np.array(self.__means)
		e = np.array(self.__diviations)
		ax.errorbar(x, y, e, linestyle='None', marker='^')
		plt.show()
		

	def readParameters(self):
		self.__problem.loadData("cubs.in")
		
class Population(object):
	"""docstring for Population"""
	def __init__(self, noIndivids, individSize):
		self.__noIndivids = noIndivids
		self.__individs = []
		for i in range(noIndivids):
			self.__individs.append(Individ(individSize))

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

	def getMean(self, problem):
		s = 0
		for i in range(self.__noIndivids):
			s += self.__individs[i].fitness(problem)
		return s / self.__noIndivids

	def getStandardDiviation(self, problem):
		m = self.getMean(problem)
		s = 0
		for i in range(self.__noIndivids):
			f = self.__individs[i].fitness(problem)
			s += (f - m) * (f - m)
		return math.sqrt(s / self.__noIndivids)


class Problem(object):
	"""docstring for Problem"""
	def __init__(self):
		self.__neighbours = {}
		self.__neighbours[1] = [3, 2, 4, 5]
		self.__neighbours[2] = [1, 3, 6, 4]
		self.__neighbours[3] = [1, 2, 6, 5]
		self.__data = []
		self.__size = 0

	def loadData(self, fileName):
		with open(fileName, "r") as f:
			self.__size = int(f.readline())
			for i in range(self.__size):
				line = f.readline()
				line = line.split(" ")
				newCube = [0]
				for j in range(6):
					newCube.append(line[j].strip())
				self.__data.append(newCube)


	def getNeighbours(self, n):
		pos = n
		if pos > 3:
			pos = 7 - pos
		return self.__neighbours[pos][:]

	def getData(self):
		return self.__data

	def getSize(self):
		return self.__size

	
if __name__ == "__main__":
	p = Problem()
	a = Algorithm(p, 40)
	a.run()





