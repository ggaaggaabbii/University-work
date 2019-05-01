import numpy
import math
import random
import os

def crossOver(a, b, n):
	newA = []
	newB = []
	for i in range(n):
		newA.append(a[b[i]])
		newB.append(b[a[i]])
	return newA, newB

def mutate(a, n):
	if random.random() < 0.05:
		pos1 = random.randint(0, n - 1)
		pos2 = random.randint(0, n - 1)
		aux = a[pos1]
		a[pos1] = a[pos2]
		a[pos2] = aux
	return a


def selectNewPopulation(population, n, costs):
	sumFitness = 0
	taken = []
	newPopulation = []

	for i in range(len(population)):
		sumFitness += 1 / fitnessFunction(population[i], n, costs)


	# eliminate unfit individuals
	lastSize = len(population) // 2
	while len(taken) < lastSize:
		val = random.random()
		percent = 0
		i = 0
		while i < len(population) and percent < val:
			percent += (1 / fitnessFunction(population[i], n, costs)) / sumFitness
			i += 1
		i -= 1
		taken.append(i)
		newPopulation.append(population[i])
		sumFitness -= 1 / fitnessFunction(population[i], n,  costs)
		population.pop(i)

	# cross-over
	for i in range(len(population) // 2):
		x = random.randint(0, lastSize - 1)
		y = random.randint(0, lastSize - 1)
		newX, newY = crossOver(newPopulation[x], newPopulation[y], n)
		newPopulation.append(newX)
		newPopulation.append(newY)

	# mutate
	for i in range(len(newPopulation)):
		newPopulation[i] = mutate(newPopulation[i], n)

	return newPopulation


def fitnessFunction(permutation, n, costs):
	fitness = 0
	for i in range(n - 1):
		if (permutation[i], permutation[i + 1]) not in costs.keys():
			return math.inf
		fitness += costs[(permutation[i], permutation[i + 1])]
	if (permutation[-1], permutation[0]) not in costs.keys():
		return math.inf
	fitness += costs[(permutation[-1], permutation[0])]
	return fitness


if __name__ == "__main__":
	with open("traveling_salesman.in") as f:
		line = f.readline()
		n = int(line.split(" ")[0])
		m = int(line.split(" ")[1])
		costs = dict()
		for i in range(m):
			line = f.readline()
			x = int(line.split(" ")[0])
			y = int(line.split(" ")[1])
			cost = int(line.split(" ")[2])
			costs[(x, y)] = cost

		#take an initial poputation of 100
		population = []
		for i in range(100):
			population.append(numpy.random.permutation(n))

		validPermutations = False
		while not validPermutations:
			validPermutations = True
			for i in range(len(population)):
				if fitnessFunction(population[i], n, costs) == math.inf:
					population[i] = population[-1]
					population[-1] = numpy.random.permutation(n)
					validPermutations = False

		alltimeBest = population[0]
		bestFitness = math.inf
		popCounter = 0

		while True:
			population = sorted(population, key = lambda permutation : fitnessFunction(permutation, n, costs))
			if fitnessFunction(population[0], n, costs) < bestFitness:
				alltimeBest = population[0]
				bestFitness = fitnessFunction(alltimeBest, n, costs)
				print("Population: ", popCounter, alltimeBest, bestFitness)
			population = selectNewPopulation(population, n, costs)
			popCounter += 1

