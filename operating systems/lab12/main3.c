#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int nrVoc = 0;
int current = 1;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

struct input{
	int ac;
	char **av;
}

int getVoc(char *str) {
	int n = strlen(str);
	for (int i = 0; i < n; ++i) {
		//...
	}
}

void* f(void* arg) {
	char** av = (struct input*)arg->av;
	int ac = (struct input*)arg->ac;
	int cond = 1;

	while (cond) {
		pthread_mutex_lock(&mtx);
		if (current < ac) {
			nrVoc += getVoc(av[current++]);
		}else {
			cond = 0;
		}
		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(int ac, char** av) {
	pthread_t t[5];
	
	struct input a;
	a.ac = ac;
	a.av = av;

	for (int i = 0; i < 5; ++i) {
		pthread_create(t + i, NULL, f, &a);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_join(t[i], NULL);
	}

	printf("%d\n", nrVoc);

	return 0;
}
