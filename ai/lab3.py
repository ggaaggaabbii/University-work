import random
import math
import matplotlib.pyplot as plt
import time
import matplotlib.animation as animation

def sigmoid(x):
  return 1 / (1 + math.exp(-x))

def getCoordonate(particle):
	p = 1
	x = 0
	y = 0

	for i in range(len(particle.getPositions()) // 2):
		x += p * particle.getPositions()[i]
		p *= 2

	p = 1

	for i in range(len(particle.getPositions()) // 2, len(particle.getPositions())):
		y += p * particle.getPositions()[i]
		p *= 2

	return x, y

POPULATION_SIZE = 6

def computeFitness(particle, problemData, numberOfNodes):
	fitness = 0
	g1 = []
	g2 = []

	for i in range(len(problemData)):
		if particle.getPositions()[i] == 1:
			g1.append(problemData[i])
		else:
			g2.append(problemData[i])

	maxim = 0
	for i in range(numberOfNodes):
		for j in range(i + 1, numberOfNodes):
			for k in range(j + 1, numberOfNodes):
				if (min(i, j), max(i, j)) not in g1:
					fitness += 1
				elif (min(i, k), max(i, k)) not in g1:
					fitness += 1
				elif (min(k, j), max(k, j)) not in g1:
					fitness += 1
				else:
					fitness -= 10
				if (min(i, j), max(i, j)) not in g2:
					fitness += 1
				elif (min(i, k), max(i, k)) not in g2:
					fitness += 1
				elif (min(k, j), max(k, j)) not in g2:
					fitness += 1
				else:
					fitness -= 10
				maxim += 1

	return fitness

class Particle():
	"""docstring for Particle"""
	def __init__(self, problemSize, problemData, numberOfNodes):
		self.__position = []
		self.__velocity = []
		self.__fitness = 0
		self.__bestPosition = []
		self.__bestFitness = 0
		self.__bestVelocity = []

		for i in range(problemSize):
			self.__velocity.append(0)
			self.__position.append(random.randint(0, 1))

		self.__fitness = computeFitness(self, problemData, numberOfNodes)
		self.__bestFitness = self.__fitness
		self.__bestPosition = self.__position[:]
		self.__bestVelocity = self.__velocity[:]

	def __str__(self):
		return str(self.__position)

	def update(self, problemData, numberOfNodes):
		for i in range(len(self.__position)):
			if sigmoid(self.__velocity[i]) > 0.5:
				self.__position[i] = 1
			else:
				self.__position[i] = 0

		f = computeFitness(self, problemData, numberOfNodes)
		self.__fitness = f
		if f > self.__bestFitness:
			self.__bestFitness = f
			self.__bestPosition = self.__position[:]
			self.__bestVelocity = self.__velocity[:]

	def evaluate(self, neighbours, problemData, numberOfNodes):
		maxim = 0
		pos = -1

		for i in range(len(neighbours)):
			if neighbours[i].getFitness() > maxim:
				maxim = neighbours[i].getFitness()
				pos = i

		#print("---------")
		#print(neighbours[pos])
		#print(self.__position)
		#print(self.__velocity)


		for i in range(len(self.__position)):
			newVelocity = 0.5 * self.__velocity[i]
			newVelocity += 0.5 * random.random() * (self.__bestPosition[i] - self.__position[i])
			newVelocity += 1.5 * random.random() * (neighbours[pos].getPositions()[i] - self.__position[i])
			self.__velocity[i] = newVelocity

		
		self.update(problemData, numberOfNodes)
		#print(self.__position)
		#print(self.__velocity)
		#print("--------")

	def getFitness(self):
		return self.__fitness

	def getPositions(self):
		return self.__position

	def getVelocity(self):
		return self.__velocity
		
class Swarm():
	"""docstring for Swarm"""
	def __init__(self, numberOfParticles, particleSize, problemData, numberOfNodes):
		self.__numberOfParticles = numberOfParticles
		self.__v = []
		self.__neighbours = {}

		for i in range(numberOfParticles):
			self.__v.append(Particle(particleSize, problemData, numberOfNodes))
			neighbours = []
			j = 0
			while j < numberOfParticles - 1:
				r = random.randint(0, numberOfParticles - 1)
				if r == i or r in neighbours:
					continue
				neighbours.append(r)
				j += 1
			self.__neighbours[i] = neighbours


	def getNeighbour(self, particle):
		neighbours = []
		for i in self.__neighbours[particle]:
			neighbours.append(self.__v[i])
		return neighbours

	def getBestParticle(self):
		maxim = -math.inf
		pos = -1
		for i in range(self.__numberOfParticles):
			#print(maxim, self.__v[i].getFitness(), pos)
			if self.__v[i].getFitness() > maxim:
				maxim = self.__v[i].getFitness()
				pos = i
		#print("best pos:" + str(pos))
		return self.__v[pos]

	def getPopulationSize(self):
		return self.__numberOfParticles

	def getPopulation(self):
		return self.__v

class Controller():
	"""docstring for Controller"""
	def __init__(self, problem):
		self.__problem = problem
		self.loadParameters()
		self.__swarm = Swarm(POPULATION_SIZE, 
			self.__problem.getProblemSize(), 
			self.__problem.getGraph(), 
			self.__problem.getNumberOfNodes()
			)
		self.__plotter = 0
		

	def iteration(self, i):
		population = self.__swarm.getPopulation()
		fitnesses = []

		ax1 = self.__plotter

		xar = []
		yar = []

		for i in range(self.__swarm.getPopulationSize()):
			fitnesses.append(population[i].getFitness())
			population[i].evaluate(self.__swarm.getNeighbour(i), 
				self.__problem.getGraph(), 
				self.__problem.getNumberOfNodes()
				)
			x1, y1 = getCoordonate(self.__swarm.getPopulation()[i])
			xar.append(int(x1))
			yar.append(int(y1))
			print(x1, y1)

		ax1.clear()
		ax1.scatter(xar,yar)
		plt.axis([-5,22,-5,22])

		plt.draw()
		plt.pause(.001)

		particle = self.__swarm.getBestParticle()
		print(particle, particle.getFitness(), fitnesses)


	def runAlg(self):
		plt.ion()
		fig = plt.figure()
		ax1 = fig.add_subplot(1,1,1)
		xar = []
		yar = []

		for i in range(self.__swarm.getPopulationSize()):
			x1, y1 = getCoordonate(self.__swarm.getPopulation()[i])
			xar.append(int(x1))
			yar.append(int(y1))
			print(x1, y1)

		self.__plotter = ax1

		ax1.clear()
		ax1.scatter(xar,yar)
		plt.show()

		#iterate = animation.FuncAnimation(fig, self.iteration, interval=1000)
		for i in range(20):
			self.iteration(ax1)
			time.sleep(1)

	def loadParameters(self):
		self.__problem.loadProblem()
		
class Problem():
	"""docstring for Problem"""
	def __init__(self, fileName):
		self.__fileName = fileName
		self.__n = 0
		self.__m = 0
		self.__graph = []

	def loadProblem(self):
		with open(self.__fileName) as f:
			line = f.readline()
			line = line.split()
			self.__n = int(line[0])
			self.__m = int(line[1])

			for i in range(self.__m):
				line = f.readline()
				line = line.split()
				x = int(line[0])
				y = int(line[1])
				
				self.__graph.append((min(x - 1, y - 1), max(y - 1, x - 1)))

	def getGraph(self):
		return self.__graph

	def getProblemSize(self):
		return len(self.__graph)

	def getNumberOfNodes(self):
		return self.__n

		
if __name__ == "__main__":
	p = Problem("graph.in")
	c = Controller(p)
	c.runAlg()

