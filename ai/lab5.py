from random import *
from math import *

EPOCH_LIMIT = 1000
LEAR_RATE = 0.1
CLASSES = 3

class Neuron:
	def __init__(self, nI = 0):
		self.noInputs = nI
		self.weights = [(random() * 2 - 1) for k in range(self.noInputs)]
		self.output = 0
		self.err = 0
    
	def activate(self, info):
		net = 0.0
		for i in range(self.noInputs):
			net += info[i] * self.weights[i]
		try:
			self.output = 1.0 / (1.0 + exp(-net))
		except OverflowError:
			if net < 0:
				self.output = 0
			else:
				self.output = 9999

	def setErr(val):
		self.err = self.output * (1 - self.output) * val

class Layer:
	def __init__(self, noN = 0, noIn = 0):
		self.noNeurons = noN
		self.neurons = [Neuron(noIn) for k in range(self.noNeurons)]

	def getNeurons(self):
		return self.neurons

class Network:
	"""docstring for Network"""
	def __init__(self, inputs = 0, outputs = 0, hiddenLayers = 0, hiddenLayersSize = 0):
		seed(1)
		self.noInputs = inputs
		self.noOutputs = outputs
		self.noHiddenLayers = hiddenLayers
		self.noNeuronsPerHiddenLayer = hiddenLayersSize
		self.layers = [Layer(self.noInputs,0)]
		self.layers += [Layer(self.noNeuronsPerHiddenLayer, self.noInputs)]
		self.layers += [Layer(self.noNeuronsPerHiddenLayer, 
							self.noNeuronsPerHiddenLayer) for k in 
							range(self.noHiddenLayers - 1)]
		self.layers += [Layer(self.noOutputs, self.noNeuronsPerHiddenLayer)]

		
	def activate(self, inputs):
		i = 0
		for n in self.layers[0].getNeurons():
			n.output = inputs[i]
			i += 1
		for l in range(1, self.noHiddenLayers + 1):
			for n in self.layers[l].getNeurons():
				info = []
				for i in range(n.noInputs):
					info.append(self.layers[l-1].neurons[i].output)
				n.activate(info)

	def errorsBackpropagate(self, err):
		#print("xd")
		#print(err)
		for l in range(self.noHiddenLayers + 1, 1, -1):
			i = 0
			for n1 in self.layers[l].getNeurons():
				if (l == self.noHiddenLayers + 1):
					n1.err = err[i]
				else:
					sumErr = 0.0
					for n2 in self.layers[l + 1].getNeurons():
						sumErr += n2.weights[i] * n2.err
					n1.err = sumErr
				for j in range(n1.noInputs):
					netWeight = n1.weights[j] + LEAR_RATE * n1.err * self.layers[l - 1].neurons[j].output
					n1.weights[j] = netWeight
				i += 1

	def errorComputationClassification(self, target, noLabels, err):
		aux = [n.getOutput() for n in self.__layers[self.__noHiddenLayers+1].getNeurons()]
        m = max(aux)
        aux = [exp(x - m) for x in aux]
        sumExp = sum(aux)
        transfOutputs = [x / sumExp for x in aux]
        computedLabel = transfOutputs.index(max(transfOutputs)) + 1
        if target == computedLabel:
            err[0] = 0
        else:
            err[0] = 1
        globalErr = err[0]
        return globalErr

	def checkGlobalErr(self,err):
		correct = sum(err)
		#print(err)
		print(correct)
		error = correct/len(err)
		if error > 0.95:
			return True
		else:
			return False


	def learning(self, inData, outData):
		stopCondition = False
		epoch = 0
		globalErr = []
		while (( not stopCondition) and (epoch < EPOCH_LIMIT)):
			globalErr = []

			print("Epoch: " + str(epoch))
			for d in range(len(inData)):
				self.activate(inData[d])	 #activate all the neurons; propagate forward the signal
				err = []		            #backpropagate the error of neurons from the output layer
				globalErr.append(self.errorComputationClassification(outData[d][0], CLASSES, err))
				self.errorsBackpropagate(err)
				#print(err)
				#for i in self.layers[self.noHiddenLayers + 1].getNeurons():
				#	print(i.err)
				#for i in self.layers:
				#	for j in i.getNeurons():
				#		print(j.weights)

			stopCondition = self.checkGlobalErr(globalErr)
			epoch += 1


def readData():
	classes = {"NO" : 1, "DH" : 2, "SL" : 3}
	trainIn = []
	trainOut = []
	testIn = []
	testOut = []

	shuffledTrainIn = []
	shuffledTrainOut = []
	shuffledTestIn = []
	shuffledTestOut = []

	with open("vertebral_column_data/train_data.in") as f:
		while True:
			line = f.readline()
			if line == "":
				break
			line = line.split()
			inputs = []
			for i in range(6):
				inputs.append(float(line[i]))
			trainIn.append(inputs)
			trainOut.append([int(classes[line[6]])])

		shuffler = []
		for i in range(len(trainIn)):
			shuffler.append(i)

		shuffle(shuffler)

		for i in range(len(trainIn)):
			shuffledTrainIn.append(trainIn[shuffler[i]])
			shuffledTrainOut.append(trainOut[shuffler[i]])
		#print(shuffledTrainIn, shuffledTrainOut)

	with open("vertebral_column_data/test_data.in") as f:
		while True:
			line = f.readline()
			if line == "":
				break
			line = line.split()
			inputs = []
			for i in range(6):
				inputs.append(float(line[i]))
			testIn.append(inputs)
			testOut.append([int(classes[line[6]])])

		shuffler = []
		for i in range(len(testIn)):
			shuffler.append(i)

		shuffle(shuffler)

		for i in range(len(testIn)):
			shuffledTestIn.append(testIn[shuffler[i]])
			shuffledTestOut.append(testOut[shuffler[i]])

	return shuffledTrainIn, shuffledTrainOut, shuffledTestIn, shuffledTestOut


if __name__ == '__main__':
	n = Network(6, 3, 2, 3)
	for i in n.layers:
		for j in i.neurons:
			print(j.weights)

	trainIn, trainOut, testIn, testOut = readData()
	n.learning(trainIn, trainOut)






