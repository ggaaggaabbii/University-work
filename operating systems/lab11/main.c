#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mtx2 = PTHREAD_MUTEX_INITIALIZER;
int count = 0, n;
int sorted = 0;

/*
3) Sa se scrie un program care citeste de la tastatura un numar intre 10 si 50. Creeaza 5 thread-uri care primesc ca si parametru numarul
citit si genereaza fiecare numere aleatoare pana cand in total s-au generat atatea numere cat este valoarea primita ca si parametru. 
Ulterior unul din cele 5 thread-uri create sorteaza crescator vectorul obtinut. Thread-ul principal va afisa rezultatul.
Exemplu:
n = 15
x = {1, 4, 2, 5, 1, 5, 66, 77, 34, 56, 23, 65, 234, 14, 15}
=> x = {1, 1, 2, 4, 5, 5, 14, 15, 23, 34, 56, 67, 66, 67, 234}
*/

void* f(void* v) {
	int* vals = (int*)v;

	while (1) {
		pthread_mutex_lock(&mtx);
		if (count < n) {
			vals[count++] = rand() % 120 + 10;
		
		} else {
			pthread_mutex_unlock(&mtx);
			break;

		}
		pthread_mutex_unlock(&mtx);
	}

	pthread_mutex_lock(&mtx2);
	if (sorted == 1) {
		pthread_mutex_unlock(&mtx2);
		return NULL;
	}

	sorted = 1;
	printf("sort\n");
	for (int i = 0; i < n - 1; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (vals[i] > vals[j]) {
				int aux = vals[i];
				vals[i] = vals[j];
				vals[j] = aux;
			}
		}
	}

	pthread_mutex_unlock(&mtx2);
	return NULL;
}

pthread_t t[5];

int main () {
	
	scanf("%d", &n);
	srand(time(NULL));

	int* v = (int*)malloc(n * sizeof(int));

	for (int i = 0; i < 5; ++i) {
		pthread_create(t + i, NULL, f, v);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_join(t[i], NULL);
	}

	for (int i = 0; i < n; ++i) {
		printf("%d\n", v[i]);
	}
	
	free(v);
	return 0;
}
