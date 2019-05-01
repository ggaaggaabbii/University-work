"""
The sliding puzzle problem – solving techniques: BFS, GBFS

@author: Goteciuc Gabriel
"""

from time import time
from collections import deque
import copy
import heapq

class Configuration:
    def __init__(self, board):
        self.__size = len(board)
        self.__board = copy.deepcopy(board)

    def __hash__(self):
        return hash(str(self.__board))

    def getSize(self):
        return self.__size
    
    def getBoard(self):
        return self.__board[:]

    def nextConfig(self):
        nextX = [1, 0, -1, 0]
        nextY = [0, 1, 0, -1]
        newConfs = []
        posX, posY = self.getEmptyPositionCoordinates()

        for i in range(4):
            newX = posX + nextX[i]
            newY = posY + nextY[i]

            if newX >= 0 and newX < self.__size and newY >= 0 and newY < self.__size:
                newBoard = copy.deepcopy(self.__board)
                newBoard[posX][posY] = newBoard[newX][newY]
                newBoard[newX][newY] = 0
                newConfs.append(Configuration(newBoard))
        return newConfs

    def __str__(self):
        s = ''
        for i in self.__board:
            for j in i:
                s += str(j) + " "
            s += "\n"
        return s

    def __eq__(self, other):
        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board[i][j] != other.getBoard()[i][j]:
                    return False
        return True

    def __lt__(self, other):
        return True
        
    def getEmptyPositionCoordinates(self):
        posX = -1
        posY = -1

        for i in range(self.__size):
            for j in range(self.__size):
                if self.__board[i][j] == 0:
                    return i, j
        return -1, -1


class Problem:
    def __init__():
        pass

    def __init__(self, initConf, finalConf):
        self.__initConf = initConf
        self.__finalConf = finalConf

    def setProblem(p):
        self.__initConf = Configuration(p)
        counter = 1
        newFinal = []
        for i in range(len(p)):
            newFinal.append([])
            for j in range(len(p)):
                newFinal[i].append(counter)
                counter = counter + 1
        self.__finalConf = Configuration(newFinal)



    def expand(self, currentConf):
        return currentConf.nextConfig()

    def getFinale(self):
        return self.__finalConf

    def getRoot(self):
        return self.__initConf

    def dist(self, value, posX, posY, size):
        if value == 0:
            rightX = size - 1
            rightY = size - 1
        else:
            rightX = (value - 1) // size;
            rightY = value - size * rightX - 1
        return (rightX - posX) * (rightX - posX) + (rightY - posY) * (rightY - posY)

    def heuristic(self, state):
        board = state.getBoard()
        distance = 0
        size = len(board)

        for i in range(size):
            for j in range(size):
                distance += self.dist(board[i][j], i, j, size)
        return distance


class Controller:
    def __init__(self, problem):
        self.__problem = problem

    def getPath(self, current, goal, parents):
        if current == goal:
            return [goal]
        return self.getPath(parents[current], goal, parents) + [current]

    def setBoard(self, p):
        self.__problem.setProblem(p)

    def setProblem(self, p):
        self.__problem = p

    def BFS(self):
        q = []
        q.append(self.__problem.getRoot())
        visited = set()
        parent = dict()

        while len(q):
            current = q.pop(0)
            visited.add(current)

            if current == self.__problem.getFinale():
                return self.getPath(self.__problem.getFinale(), self.__problem.getRoot(), parent)
            for i in self.__problem.expand(current):
                if i in visited:
                    continue
                parent[i] = current
                q.append(i)
        return []

    def GBFS(self):
        q = []
        heapq.heappush(q, (self.__problem.heuristic(self.__problem.getRoot()), self.__problem.getRoot()))
        visited = set()
        parent = dict()

        while len(q):
            current = heapq.heappop(q)[1]
            visited.add(current)

            if current == self.__problem.getFinale():
                return self.getPath(self.__problem.getFinale(), self.__problem.getRoot(), parent)
            for i in self.__problem.expand(current):
                if i in visited:
                    continue
                parent[i] = current
                heapq.heappush(q, (self.__problem.heuristic(i), i))
        return []


class Ui:
    def __init__(self):
        self.__init = Configuration([[4, 7, 3], [1, 5, 8], [6, 2, 0]])
        self.__fin = Configuration([[1, 2, 3], [4, 5, 6], [7, 8, 0]])
        p = Problem(self.__init, self.__fin)
        self.__ctrl = Controller(p)

    def printMenu(self):
        s = ''
        s += 'Menu:\n'
        s += "0. Exit\n"
        s += "1. Read Configuration\n"
        s += "2. Get BFS Path\n"
        s += "3. Get GBFS Path\n"
        print(s)

    def readConfig(self):
        fileName = input("cfg file name: ")
        try:
            with open(fileName) as f:
                board = []
                n = int(f.readline())
                for i in range(n):
                    line = f.readline()
                    numbers = line.split(" ")
                    board.append([])
                    for j in range(n):
                        board[i].append(int(numbers[j]))
        except:
            print("Invalid cfg file")

    def printBFSPath(self):
        startClock = time()
        for i in self.__ctrl.BFS():
            print(str(i) + "\n")
        print('execution time = ',time() - startClock, " seconds" )

    def printGBFSPath(self):
        startClock = time()
        for i in self.__ctrl.GBFS():
            print(str(i) + "\n")
        print('execution time = ',time() - startClock, " seconds" )

    def start(self):
        self.printMenu()
        while True:
            try:
                command = int(input(">> "))
                if command == 0:
                    return
                elif command == 1:
                    self.readConfig()
                elif command == 2:
                    self.printBFSPath()
                elif command == 3:
                    self.printGBFSPath()
            except Exception as e:
                print(e)
                print("Invalid command")


if __name__ == '__main__':
    u = Ui()
    u.start()
