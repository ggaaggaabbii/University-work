import math
import random
import heapq


def crossOver(a, b):
	newA = []
	newB = []

	for i in range(len(a)):
		if random.random() < 0.5:
			newX = a[i][0]
		else:
			newX = b[i][0]
		if random.random() < 0.5:
			newY = a[i][1]
		else:
			newY = b[i][1]
		newA.append((newX, newY))

		if random.random() < 0.5:
			newX = a[i][0]
		else:
			newX = b[i][0]
		if random.random() < 0.5:
			newY = a[i][1]
		else:
			newY = b[i][1]
		newB.append((newX, newY))

	return newA, newB


def mutation(a):
	if random.random() < 0.05:
		pos = random.randint(0, len(a) - 1)
		newX = a[pos][0]
		newY = a[pos][1]

		if random.random() < 0.5:
			newY += random.randint(-1, 1)
			if newY < 0:
				newY = 0
			if newY >= len(a):
				newY = len(a) - 1
		else:
			newX += random.randint(-1, 1)
			if newX < 0:
				newX = 0
			if newX >= len(a):
				newX = len(a) - 1
		a[pos] = (newX, newY)
	return a

def dijkstra(pos, customers, costs, n, m, matrix, replies):
	heap = []
	visited = set()
	newX = [-1, 0, 1, 0]
	newY = [0, 1, 0, -1]

	heapq.heappush(heap, (0, pos))
	#print("---" * 100)
	#print(pos, customers, costs, n, m, matrix, replies)
	#print("---" * 100)

	while len(heap) > 0:
		newCustomer = heapq.heappop(heap)
		cost = newCustomer[0]
		newCustomer = newCustomer[1]
		visited.add(newCustomer)

		if newCustomer in replies:
			if (cost != -math.inf):
				return customers[pos] - cost
			return -math.inf

		for i in range(4):
			newx = newCustomer[0] + newX[i]
			newy = newCustomer[1] + newY[i]
			if newx >= 0 and newx < n and newy >= 0 and newy < m:
				if (newx, newy) not in visited:
					heapq.heappush(heap, (cost + costs[matrix[newx][newy]], (newx, newy)))

	return -math.inf

def fitnessFunction(individ, customers, costs, matrix, n, m):
	s = 0

	for i in customers.keys():
		s += dijkstra(i, customers, costs, n, m, matrix, individ)

	return s

def selectNewPopulation(population, n, m, matrix, customers, costs):
	sumFitness = 0
	taken = []
	newPopulation = []

	for i in range(len(population)):
		sumFitness += fitnessFunction(population[i], customers, costs, matrix, n, m)

	sumFitness = max(1, sumFitness)
	# eliminate unfit individuals
	lastSize = len(population) // 2
	while len(taken) < lastSize:
		val = random.random()
		percent = 0
		i = 0
		while i < len(population) and percent < val:
			percent += (fitnessFunction(population[i], customers, costs, matrix, n, m)) / sumFitness
			i += 1
		i -= 1
		taken.append(i)
		newPopulation.append(population[i])
		sumFitness -= fitnessFunction(population[i], customers, costs, matrix, n, m)
		population.pop(i)

	# cross-over
	for i in range(len(population) // 2):
		x = random.randint(0, lastSize - 1)
		y = random.randint(0, lastSize - 1)
		newX, newY = crossOver(newPopulation[x], newPopulation[y])
		newPopulation.append(newX)
		newPopulation.append(newY)

	# mutate
	for i in range(len(newPopulation)):
		newPopulation[i] = mutation(newPopulation[i])

	return newPopulation



if __name__ == "__main__":
	with open("f.in") as f:
		line = f.readline()
		line = line.split(" ")
		m = int(line[0])
		n = int(line[1])
		c = int(line[2])
		r = int(line[3])
		matrix = []
		customers = dict()

		costs = dict()
		costs["#"] = math.inf
		costs["~"] = 800
		costs["*"] = 200
		costs["+"] = 150
		costs["X"] = 120
		costs["_"] = 100
		costs["H"] = 70
		costs["T"] = 50

		for i in range(c):
			line = f.readline()
			line = line.split(" ")
			customers[(int(line[1]), int(line[0]))] = int(line[2])

		for i in range(n):
			line = f.readline()
			matrix.append(line)

		population = []
		for k in range(1000):
			newIndividual = []
			for i in range(r):
				newIndividual.append((random.randint(0, n), random.randint(0, m)))
			population.append(newIndividual)


		bestFitness = -math.inf
		alltimeBest = population[0]
		popCounter = 0

		
		#while True:
		print(popCounter)
		population = sorted(population, key = lambda individ : -fitnessFunction(individ, customers, costs, matrix, n, m))
		scor = fitnessFunction(population[0], customers, costs, matrix, n, m)
		#print(scor)
		if scor > bestFitness:
			alltimeBest = population[0]
			bestFitness = scor
			print("Population: ", popCounter, alltimeBest, bestFitness)
		#print("Population: ", popCounter, alltimeBest, bestFitness)
		population = selectNewPopulation(population, n, m, matrix, customers, costs)
		popCounter += 1
		






