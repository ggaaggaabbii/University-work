#include <fstream>
#include <iostream>
#include <string.h>
using namespace std;

ofstream fout("output.out");

int currentFunction = 0;

bool validate(int **M, int n) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j)
      for (int k = 1; k <= n; ++k)
        if (M[M[i][j]][k] != M[i][M[j][k]])
          return false;
  return true;
}

void printToFile(int **M, int n) {
  fout << "function number " << currentFunction + 1 << " : \n";
  for (int i = 1; i <= n; ++i) {
    fout << '\t';
    for (int j = 1; j <= n; ++j)
      fout << char(M[i][j] + 'a' - 1) << ' ';
    fout << '\n';
  }
  fout << '\n';
}

void bktr(int **M, int currentStep, int n) {

  if (currentStep == n * n + 1) {
    if (validate(M, n)) {
      printToFile(M, n);
      ++currentFunction;
    }
    return;
  }
  for (int i = 1; i <= n; ++i) {
    M[(currentStep % n == 0 ? currentStep / n - 1 : currentStep / n) + 1]
     [currentStep % n == 0 ? n : currentStep % n] = i;
    bktr(M, currentStep + 1, n);
  }
}

int main() {
  int n = 0, **M;
  cout << "Give a number: ";
  cin >> n;
  M = new int *[n + 2];
  for (int i = 0; i <= n + 2; ++i) {
    M[i] = new int[n + 2];
  }
  bktr(M, 1, n);
  return 0;
}
