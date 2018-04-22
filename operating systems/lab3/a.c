// se citeste o secventa de numere si se afiseaza suma lor
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int* x;
	int sum = 0;
	int count = 0;

	x = malloc(sizeof(int) * 11);

	for (i = 0; i <= 10; i++) {
		scanf("%d", &x[i]);
		sum = sum + x[i];
		count++;
	}
	printf("media: %d\n", sum/count);
	free(x);
	return 0;
}
