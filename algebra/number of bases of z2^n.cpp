#include <iostream>
#include <fstream>

using namespace std;

ofstream g("output.out");

double **Result;
long long MAXVAL, numberOfBases;

void swapLines(double **M, int n, int line1, int line2){
	for (int i = 1; i <= n; ++i)
		swap(M[line1][i], M[line2][i]);
}

void substractLines(double **M, int n, int mainLine, int otheLine, double value){
	for (int i = 1; i <= n; ++i){
		M[mainLine][i] -= value * M[otheLine][i];
	}
}

double gaussDeterminant(double **M, int n){
	int ok;
	double determinant = 1;
	for (int i = 1; i <= n; ++i){
		if (M[i][i] == 0){
			ok = 0;
			for (int j = i + 1; j <= n; ++j){
				if (M[j][i] != 0){
					swapLines(M, n, i, j);
					ok = 1;
					break;
				}
			}
			if (ok == 0)
				return 0;
		}
		determinant *= M[i][i];
		for (int j = i + 1; j <= n; ++j){
			if (M[j][i] != 0){
				double value = M[j][i] / M[i][i];
				substractLines(M, n, j, i, value);
			}
		}
	}
	return int(determinant);
}

void printResult(double **M, int n){

g << "basis number: " << ++numberOfBases << '\n' << "<";
	for (int i = 1; i <= n; ++i){
		g << "(";
		for (int j = 1; j < n; ++j){
			g << M[i][j] << ", ";
		}
		g << M[i][n];
		g << ") ";
	}
	g << ">\n";
}

void makeCopy(double **Result, double **M, int n){
	for (int i = 1; i <= n; ++i){
		for (int j = 1; j <= n; ++j){
			Result[i][j] = M[i][j];
		}
	}
}

void computeSpace(int step, int finalStep, double **M){
	if (step == finalStep + 1){
		makeCopy(Result, M, finalStep);
		if (int (gaussDeterminant(M, finalStep)) % 2 != 0){
			printResult(Result, finalStep);
		}
		makeCopy(M, Result, finalStep);
		return;
	}
	int aux;
	for (int i = 1; i <= MAXVAL; ++i){
		aux = i;
		for (int j = 1; j <= finalStep; ++j){
			M[step][j] = aux % 2;
			aux /= 2;
		}
	computeSpace(step + 1, finalStep, M);
	}
}

long long result[20000];

void multiply(int value){
  unsigned long T = 0;

	for (int i = 1;i <= result[0]; ++i){
		result[i] = result[i] * value + T;
		T = result[i] / 10;
		result[i] = result[i] % 10;
	}
	while (T){
		result[++result[0]] = T % 10;
		T/=10;
	}
}

int basisCounter(int n){
	result[0] = 1;
	result[1] = 1;
	long long aux = (1 << n) - 1;
	for (int i = 1; i <= n; ++i){
		multiply(aux);
		aux -= (1 << (i - 1));
	}
	for (int i = result[0]; i > 0; --i){
		g << result[i];
	}
}

int main(){
	int n;
	double **M;
	cout << "Introduce the dimension of the space: ";
	cin >> n;
	MAXVAL = (1 << n) - 1;
	M = new double *[n + 2];
	Result = new double *[n + 2];
	for (int i = 0; i < n + 2; ++i){
		M[i] = new double [n + 2];
		Result[i] = new double [n + 2];
	}

	g << "Total number of bases is: ";
	basisCounter(n);
	g << '\n';

	if (n <= 5)
		computeSpace(1, n, M);
	
	return 0;
}
