#include <pthread.h>
#include <stdio.h>

int sum = 0;

//pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* func(void* arg)
{
	int i;
	int nr = (int)(size_t)arg;

	for (i = nr; i < nr+100; i++)
	{
		//pthread_mutex_lock(&mtx);
		sum += i;
		//pthread_mutex_unlock(&mtx);
	}

	return NULL;
}

int main()
{
	int i;
	pthread_t th[10];

	for (i = 0; i < 10; i++)
	{
		pthread_create(&th[i], NULL, func, (void*)(size_t)(i*100+1));
	}

	for (i = 0; i < 10; i++)
	{
		pthread_join(th[i], NULL);
	}

	printf("sum=%d\n", sum);

	return 0;
}
