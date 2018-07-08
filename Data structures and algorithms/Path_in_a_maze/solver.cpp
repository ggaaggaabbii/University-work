#include "solver.h"

struct Point
{
	int x;
	int y;
};

int lX[] = { -1, 0, 1, 0}, lY[] = {0, -1, 0, 1}; // necessary to calculate the next positions

void bfs(int** M, int initX, int initY, int &exitX, int &exitY, int n, int m) {
	Queue<Point> Q;
	int newX, newY;

	Point initalP;
	initalP.x = initX;
	initalP.y = initY;

	M[initX][initY] = 1;
	Q.push(initalP);

	while (!Q.isEmpty()) {
		Point aux = Q.pop();
		for (int i = 0; i < 4; ++i) {
			newX = aux.x + lX[i];
			newY = aux.y + lY[i];
			if (M[newX][newY] == 0) {
				M[newX][newY] = M[aux.x][aux.y] + 1;
				if (newX == 0 || newX > n || newY == 0 || newY > m) {
					exitX = newX;
					exitY = newY;
					return;
				}
				initalP.x = newX;
				initalP.y = newY;
				Q.push(initalP);
			}
		}
	}
	exitX = -1;
	exitY = -1;
}

int calculateHeuristic(int x, int y, int n, int m) {
	int val = y;
	val = std::min(val, m - y);
	val = std::min(val, n - x);
	val = std::min(val, x);
	return val;
}

void aStar(int** M, int initX, int initY, int &exitX, int &exitY, int n, int m) {
	PriorityQueue<Point, int> PQ;
	int newX, newY, cost;
	Point initalP;
	initalP.x = initX;
	initalP.y = initY;

	M[initX][initY] = 1;
	PQ.push(initalP, calculateHeuristic(initX, initY, n, m));

	while (!PQ.isEmpty()) {
		Point aux;
		PQ.pop(aux, cost);
		for (int i = 0; i < 4; ++i) {
			newX = aux.x + lX[i];
			newY = aux.y + lY[i];
			if (M[newX][newY] == 0) {
				M[newX][newY] = M[aux.x][aux.y] + 1;
				if (newX == 0 || newX > n || newY == 0 || newY > m) {
					exitX = newX;
					exitY = newY;
					return;
				}
				initalP.x = newX;
				initalP.y = newY;

				PQ.push(initalP, calculateHeuristic(newX, newY, n, m));
			}
		}
	}
	exitX = -1;
	exitY = -1;
}

void readInput(std::string file, int*** M, int& initX, int& initY, int& n, int& m) {
	std::ifstream f(file);
	char c;
	f >> n >> m;
	(*M) = new int*[n + 2];

	for (int i = 0; i < n + 2; ++i) {
		(*M)[i] = new int[m + 2];
	}
	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j <= m + 1; ++j) {
			(*M)[i][j] = 0;
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			f >> c;
			if (c == 'X') {
				(*M)[i][j] = -1; //occupied
			} else if (c == 'R') {
				initX = i;
				initY = j;
			}
		}
	}
}

void deleteMatrix(int **M, int n, int m) {
	for (int i = 0; i < n + 2; ++i) {
		delete[] M[i];
	}
	delete[] M;
}

bool checkPath(std::string file) {
	int n, m, **M = nullptr, initX, initY, exitX, exitY;
	std::ifstream f(file);

	readInput(file, &M, initX, initY, n, m);

	aStar(M, initX, initY, exitX, exitY, n, m);

	deleteMatrix(M, n, m);

	f.close();
	return exitX != -1;
}

void retrivePath(int **M, int initX, int initY, int exitX, int exitY, int n, int m) {
	if (initX == exitX && initY == exitY) {
		std::cout << initX << ", " << initY << " -> ";
		return;
	}
	for (int i = 0; i < 4; ++i) {
		int newX = exitX + lX[i];
		int newY = exitY + lY[i];
		if (newX > 0 && newX <= n && newY > 0 && newY <= m &&
		        M[newX][newY] == M[exitX][exitY] - 1) {
			retrivePath(M, initX, initY, newX, newY, n, m);
			std::cout << exitX << ", " << exitY << " -> ";
			return;
		}
	}
}

void path(std::string file) {
	int n, m, **M = nullptr, initX, initY, exitX, exitY;
	if (!checkPath(file)) {
		std::cout << "No path\n";
		return;
	}
	std::ifstream f(file);

	readInput(file, &M, initX, initY, n, m);

	aStar(M, initX, initY, exitX, exitY, n, m);
	retrivePath(M, initX, initY, exitX, exitY, n, m);
	std::cout << "\n";

	deleteMatrix(M, n, m);

	f.close();
}

void lowestPath(std::string file) {
	int n, m, **M = nullptr, initX, initY, exitX, exitY;
	if (!checkPath(file)) {
		std::cout << "No path\n";
		return;
	}
	std::ifstream f(file);

	readInput(file, &M, initX, initY, n, m);

	bfs(M, initX, initY, exitX, exitY, n, m);

	retrivePath(M, initX, initY, exitX, exitY, n, m);
	std::cout << "\n";

	deleteMatrix(M, n, m);

	f.close();
}