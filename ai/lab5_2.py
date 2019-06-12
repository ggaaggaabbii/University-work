import math
import numpy as np
from random import *
import pickle


class Connection:
    def __init__(self, connectedNeuron):
        self.connectedNeuron = connectedNeuron
        self.weight = np.random.normal()
        self.dWeight = 0.0


class Neuron:
    eta = 0.01
    alpha = 0.1

    def __init__(self, layer):
        self.dendrons = []
        self.error = 0.0
        self.gradient = 0.0
        self.output = 0.0
        if layer is None:
            pass
        else:
            for neuron in layer:
                con = Connection(neuron)
                self.dendrons.append(con)

    def addError(self, err):
        self.error = self.error + err

    def sigmoid(self, x):
        try:
            rez = 1 / (1 + math.exp(-x * 1.0))
        except OverflowError:
            if x < 0:
                rez = 0
            else:
                rez = 1
        return rez

    def dSigmoid(self, x):
        return x * (1.0 - x)

    def setError(self, err):
        self.error = err

    def setOutput(self, output):
        self.output = output

    def getOutput(self):
        return self.output

    def feedForword(self):
        sumOutput = 0
        if len(self.dendrons) == 0:
            return
        for dendron in self.dendrons:
            sumOutput = sumOutput + dendron.connectedNeuron.getOutput() * dendron.weight
        self.output = self.sigmoid(sumOutput)

    def backPropagate(self):
        self.gradient = self.error * self.dSigmoid(self.output);
        for dendron in self.dendrons:
            dendron.dWeight = Neuron.eta * (
            dendron.connectedNeuron.output * self.gradient) + self.alpha * dendron.dWeight;
            dendron.weight = dendron.weight + dendron.dWeight;
            dendron.connectedNeuron.addError(dendron.weight * self.gradient);
        self.error = 0;


class Network:
    def __init__(self, topology):
        self.layers = []
        for numNeuron in topology:
            layer = []
            for i in range(numNeuron):
                if (len(self.layers) == 0):
                    layer.append(Neuron(None))
                else:
                    layer.append(Neuron(self.layers[-1]))
            layer.append(Neuron(None))
            layer[-1].setOutput(1)
            self.layers.append(layer)

    def setInput(self, inputs):
        for i in range(len(inputs)):
            self.layers[0][i].setOutput(inputs[i])

    def feedForword(self):
        for layer in self.layers[1:]:
            for neuron in layer:
                neuron.feedForword();

    def backPropagate(self, target):
        for i in range(len(target)):
            self.layers[-1][i].setError(target[i] - self.layers[-1][i].getOutput())
        for layer in self.layers[::-1]:
            for neuron in layer:
                neuron.backPropagate()

    def getError(self, target):
        err = 0
        for i in range(len(target)):
            e = (target[i] - self.layers[-1][i].getOutput())
            err = err + e ** 2
        err = err / len(target)
        err = math.sqrt(err)
        return err

    def getResults(self):
        output = []
        for neuron in self.layers[-1]:
            output.append(neuron.getOutput())
        output.pop()
        return output

    def getThResults(self):
        output = []
        maxim = 0.0
        for neuron in self.layers[-1]:
            o = neuron.getOutput()
            if (o > 0.5):
                output.append(1)
            else:
                output.append(0)
        """
        for neuron in self.layers[-1]:
            o = neuron.getOutput()
            if (o == maxim):
                output.append(1)
            else:
                output.append(0)
        """
        output.pop()

        return output

def read(filename):
    classes = {"NO" : 1, "DH" : 2, "SL" : 3}
    In = []
    Out = []

    shuffledIn = []
    shuffledOut = []

    with open(filename) as f:
        while True:
            line = f.readline()
            if line == "":
                break
            line = line.split()
            inputs = []
            outs = []
            for i in range(6):
                inputs.append(float(line[i]))
            In.append(inputs)
            expected = int(classes[line[6]])
            k = 0
            while k < expected - 1:
                outs.append(0)
                k += 1
            outs.append(1)
            k += 1
            while k < 3:
                outs.append(0)
                k += 1
            Out.append(outs)

        shuffler = []
        for i in range(len(In)):
            shuffler.append(i)

        shuffle(shuffler)

        for i in range(len(In)):
            shuffledIn.append(In[shuffler[i]])
            shuffledOut.append(Out[shuffler[i]])
        #print(shuffledIn, shuffledOut)
    return shuffledIn, shuffledOut

def readData():
    print("reading...")
    trainIn, trainOut = read("vertebral_column_data/train_data.in")
    testIn, testOut = read("vertebral_column_data/test_data.in")
    return trainIn, trainOut, testIn, testOut


def main():
    topology = []
    topology.append(6)
    topology.append(7)
    topology.append(7)
    topology.append(3)
    #pickle_in = open("network2.pickle","rb")
    #net = pickle.load(pickle_in)
    net = Network(topology)
    Neuron.eta = 0.15
    Neuron.alpha = 0.015

    trainIn, trainOut, testIn, testOut = readData()
    
    #learn
    while True:

        err = 0
        s = 0
        for i in range(len(trainIn)):
            net.setInput(trainIn[i])
            net.feedForword()
            rez = net.getThResults()
            for j in range(3):
                if trainOut[i][j] != rez[j]:
                    s += 1
                    break
            
            net.backPropagate(trainOut[i])
            err = err + net.getError(trainOut[i])

        if ((len(trainIn) - s) / len(trainIn)) > 0.75:
                break

        print("error: " + str(err), "accuracy: " + str(((len(trainIn) - s) / len(trainIn))))
    
    
    s = 0
    for i in range(len(testIn)):
        print("expected: " + str(testOut[i]))
        net.setInput(testIn[i])
        net.feedForword()
        rez = net.getThResults()
        print("got: " + str(rez))
        for j in range(3):
            if testOut[i][j] != rez[j]:
                s += 1
                break

    print("accuracy: " + str((len(testIn) - s) / len(testIn)))
    
    pickle_out = open("network2.pickle","wb")
    pickle.dump(net, pickle_out)
    pickle_out.close()


if __name__ == '__main__':
    main()