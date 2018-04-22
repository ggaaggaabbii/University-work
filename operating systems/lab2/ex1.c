#include <stdio.h>
#include <stdlib.h>

int main() {
	int i;
	int *x = malloc(10 * sizeof(int));
	for (i = 0; i < 10; ++i) {
		scanf("%d", &x[i]);
	}
	free(x);
	return 0;
}
