#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<vector<int>> Results;
int contor = 0;
long long Pow(long long number, long long power){
	if (power == 0)
		return 1;
	long long c = Pow(number, power / 2);
	c *= c;
	if (power % 2 == 1)
		c *= number;
	return c;
}

void swapLines(double **M, int n, int line1, int line2){
	for (int i = 1; i <= n; ++i)
		swap(M[line1][i], M[line2][i]);
}

void substractLines(double **M, int n, int mainLine, int otheLine, double value){
	for (int i = 1; i <= n; ++i){
		M[mainLine][i] -= value * M[otheLine][i];
	}
}

void swap(int **mat, int R, int C, int row1, int row2,
          int col)
{
    for (int i = 0; i < col; i++)
    {
        int temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}
int rankOfMatrix(int **mat, int R, int C)
{
    int rank = C;
 
    for (int row = 0; row < rank; row++){
        if (mat[row][row]){
           for (int col = 0; col < R; col++){
               if (col != row){
                 double mult = (double)mat[col][row] /
                                       mat[row][row];
                 for (int i = 0; i < rank; i++){
                	mat[col][i] -= mult * mat[row][i];
                	mat[col][i] = (2 + mat[col][i]) % 2;
                }
              }
           }
        }else{
            bool reduce = true;
            for (int i = row + 1; i < R;  i++){
                if (mat[i][row]){
                    swap(mat, R, C, row, i, rank);
                    reduce = false;
                    break ;
                }
            }
            if (reduce){
                rank--;
                for (int i = 0; i < R; i ++)
                    mat[i][row] = mat[i][rank];
            }
            row--;
        }
    }
    return rank;
}


bool liniarIndep(int **M, int n, int k){
	int **M2;
	M2 = new int*[n + 1];
	for (int i = 0; i <= n; ++i){
		M2[i] = new int[k + 1];
	}
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < k; ++j){
			M2[i][j] = M[i][j];
		}
	}
	int res = rankOfMatrix(M2, n, k);
	return (res == k);
}


void addToMatrix(int **M, int nr, int n, int step){
	for (int i = 0; i < n ;++i){
		M[n - i - 1][step - 1] = nr % 2;
		nr /= 2;
	}
}

void verifUniqueness(int **M, int n, int k){

	int **Mcurrent;
	Mcurrent = new int*[n + 2];
	for (int i = 0; i <= n; ++i){
		Mcurrent[i] = new int[2 * k + 2];
	}

	for (auto it:Results){
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < k; ++j){
				Mcurrent[i][j] = it[i * k + j];
			}
		}
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < k; ++j){
				Mcurrent[i][j + k] = M[i][j];
			}
		}
		int res = rankOfMatrix(Mcurrent, n, 2 * k);
		if (res == k){
			return;
		}
	}
	vector <int> newSolution;
	for (int i = 0; i < n; ++i){
		for (int j = 0; j < k; ++j){
			newSolution.push_back(M[i][j]);
		}
	}
	Results.push_back(newSolution);
}

void back(int step, int **M, int last, int n, int k){
	if (step == k + 1){
		if (liniarIndep(M, n, k)){
			contor ++;
			verifUniqueness(M, n, k);
		}
		
		return;
	}

	for (int i = last + 1; i <= (1 << n) - 1; ++i){
		addToMatrix(M, i, n, step);
		
		back(step + 1, M, i, n, k);
	}
}



long long numberOfSubspaces(int n, int k){

	long long power = 1;
	for (int i = 0; i <= k - 1; ++i){
		power *= (Pow(2, n) - Pow(2, i));
	}
	for (int i = 0; i <= k - 1; ++i){
		power /= (Pow(2, k) - Pow(2, i));
	}
	return power;
}

int main()
{
	int n, k;
	cout << "n = ";
	cin >> n;
	cout << "k = ";
	cin >> k;
	ofstream g("output.out");

	int **M;
	M = new int*[n + 2];
	for (int i = 0; i <= n; ++i){
		M[i] = new int[k + 2];
	}
	g << numberOfSubspaces(n, k) << '\n';
	back(1, M, 0, n, k);
	for (auto it:Results){
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < k; ++j){
				M[i][j] = it[i * k + j];
			}
		}
		g << "<";
		for (int i = 0; i < k; ++i){
			g << "( ";
			for (int j = 0; j < n - 1; ++j){
				g << M[j][i] << ", ";
			}
			g << M[n - 1][i];
			g << ")";
			if (i < k -1)
				g << ", ";
		}
		g << ">\n";
		
	}
	//g<< Results.size();
	
	return 0;
}
