#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swp(char **a, char **b){
	char *aux;
	aux = *b;
	*b = *a;
	*a = aux;
}

int main() {
	int n;
	char **matrix;
	scanf("%d", &n);
	matrix = malloc(n * sizeof(char*));
	for (int i = 0; i < n; ++i) {
		matrix[i] = malloc(11 * sizeof(char));
		scanf("%s", matrix[i]);
	}

	int ok;
	do{
		ok = 1;
		for (int i = 0; i < n - 1; ++i){
			if (strcmp(matrix[i], matrix[i + 1]) > 0){
				ok = 0;
				swp(&matrix[i], &matrix[i + 1]);
			}
		}
	}while (ok == 0);
	
	for(int i = 0; i < n; ++i) {
		printf("%s\n", matrix[i]);
	}

	for(int i = 0; i < n; ++i) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}

