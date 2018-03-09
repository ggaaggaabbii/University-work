#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
checks if a number is prime
input: an integer
output: 0 if the number is not prime, 1 if it is
*/
int isPrime(int n) {
	if (n < 2)
		return 0;
	if (n % 2 == 0 && n != 2)
		return 0;
	for (int d = 3; d * d <= n; d += 2)
		if (n % d == 0)
			return 0;
	return 1;
}

typedef struct {
	int a, b;
} pair;

void testIsPrime() {
	assert(isPrime(-1) == 0);
	assert(isPrime(0) == 0);
	assert(isPrime(1) == 0);
	assert(isPrime(4) == 0);
	assert(isPrime(10) == 0);
	assert(isPrime(2) == 1);
	assert(isPrime(3) == 1);
	assert(isPrime(5) == 1);
	assert(isPrime(7) == 1);
}

void citire(int *n) {
	scanf("%d", n);
}

pair* solve(int n) {
	int count = 2, c = 0;
	pair *v = (pair*)malloc(sizeof(pair) * n);
	while (n) {
		if (isPrime(count) && isPrime(count + 2)) {
			v[c].a = count;
			v[c++].b = count + 2;
			//printf("%d %d\n", count, count + 2);
			--n;
		}
		++count;
	}
	return v;
}

void afis(pair *v, int n) {
	for (int i = 0; i < n; ++i) {
		printf("%d %d\n", v[i].a, v[i].b);
	}
}

int main() {
	//testIsPrime();
	int n;
	citire(&n);
	pair * v = solve(n);
	afis(v, n);
	free(v);
	return 0;
}