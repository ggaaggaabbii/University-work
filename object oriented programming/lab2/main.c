#include "functionality.h"

void printResult(Result r) {
	printf("%s\n", "The subsequence is:");
	for (int i = 0; i < r.length; ++i) printf("%d ", r.start[i]);
	printf("\n");
}

int main() {
	double x;
	int n;
	int *List = 0;
	char op[100];
	Result r;
	while (1) {
		printf("%s\n%s\n%s\n%s\n",
		       "Choose a functionality:",
		       "a. Determine the value x^n, where x is a real number and n is a natural number",
		       "b. Longest contiguous subsequence such that any two consecutive elements have contrary signs",
		       "Press 0 to exit");

		scanf("%s", op);
		if (strcmp(op, "0") == 0) break;
		else if (strcmp(op, "a") == 0) {
			printf("%s\n", "Give values to x and n:");
			scanf("%lf", &x);
			scanf("%d", &n);
			printf("The result is: %lf\n", power(x, n));
		}
		else if (strcmp(op, "b") == 0) {
			printf("%s\n", "Give the length of the list:");
			scanf("%d", &n);
			printf("%s\n", "Give the elements of the lsit:");

			List = (int*)malloc(sizeof(int) * (n + 1));
			for (int i = 0; i < n; ++i) scanf("%d", List + i);
			r = subsequence(List, n);
			printResult(r);
			free(List);
		} else printf("%s\n", "Invalid input");
	}
	return 0;
}