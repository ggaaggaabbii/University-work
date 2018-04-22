#include <stdio.h>
#include <stdlib.h>

int main() {
	int *v = malloc(10 * sizeof(int)), sum = 0, Min, Max;
	scanf("%d", v);
	Min = Max = sum = v[0];
	for (int i = 1; i < 10; ++i){
		scanf("%d", v + i);
		if (v[i] < Min) Min = v[i];
		if (v[i] > Max) Max = v[i];
		sum += v[i];
	}
	printf("min: %d\nmax: %d\nsum: %d\navg: %lf\n", Min, Max, sum, 1.0 * sum / 10);
	free(v);
}
