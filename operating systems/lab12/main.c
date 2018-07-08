#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int n;
int position;
pthread_mutex_t mtx;

void* f(void* arg) {
	char *str = (char*)arg;

	while (1) {
		pthread_mutex_lock(&mtx);
		if (position <= n - 1){
			char c = rand() % 26 + 'a';
			str[position++] = c;
		}else {
			pthread_mutex_unlock(&mtx);
			return NULL;
		}
		pthread_mutex_unlock(&mtx);
	}
}

int main() {
	srand(time(NULL));
	scanf("%d", &n);
	char* str = malloc(sizeof(char) * (n + 1));
	position = strlen(str);
	pthread_t t[5];

	for (int i = 0; i < 5; ++i) {
		pthread_create(t + i, NULL, f, str);
	}

	for (int i = 0; i < 5; ++i) {
		pthread_join(t[i], NULL);
	}

	printf("%s\n", str);
	free(str);
	
	return 0;
}
