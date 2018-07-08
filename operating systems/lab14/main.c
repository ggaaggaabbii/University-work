#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int g;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
int current;
int ids[5];

void* f(void* arg) {
	int id = *(int*)arg;
	int val = rand() % 10;

	while (1) {
		pthread_mutex_lock(&mtx);

		if (g <= 0) {
			pthread_mutex_unlock(&mtx);
			return NULL;
		}

		if (current == id) {
			printf("Threadul %d decrementeaza %d cu %d si ramane %d \n", id, g, val, g - val);
			g -= val;
			val = rand() % 10;
			current = (current + 1) % 5;
		}

		pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main(int ac, char** av) {
	pthread_t t[5];
	srand(time(NULL));

	printf("Dati g: ");
	scanf("%d", &g);
	current = 0;
	
	for (int i = 0; i < 5; ++i) {
		ids[i] = i;
		pthread_create(t + i, NULL, f, ids + i);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_join(t[i], NULL);
	}

	return 0;
}
