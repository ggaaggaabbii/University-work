#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx[5];

int val = 0;
int n;

void* f(void* arg) {
	int ord = (int)arg;
	int cond = 1;
	while (cond){
		pthread_mutex_lock(&mtx[ord]);
		if (val < n) {
			int added = rand() % 10;
			val += added;
			printf("Thread %d added %d total %d\n", 
							ord, added, val);
			pthread_mutex_unlock(&mtx[(ord + 1) % 5]);
		} else {
			pthread_mutex_unlock(&mtx[(ord + 1) % 5]);
			pthread_mutex_unlock(&mtx[ord]);
			cond = 0;
		}
	}
	return NULL;
}

int main(int ac, char **av) {
	if (ac < 2) {
		return 0;
	}
	n = atoi(av[1]);
	pthread_t t[5];

	for (int i = 1; i < 5; ++i){
		pthread_mutex_lock(&mtx[i]);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_create(t + i, NULL, f, i);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_join(t[i], NULL);
	}

	return 0;
}
