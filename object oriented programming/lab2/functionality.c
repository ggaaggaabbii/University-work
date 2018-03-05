#include "functionality.h"

double power(double x, int n) {
	if (n == 0)
		return 1;
	double aux = power(x, n / 2);
	aux *= aux;
	if (n & 1)
		aux *= x;
	return aux;
}

int sign(int n) {
	if (n >= 0) return 1;
	return -1;
}

Result subsequence(int *v, int length) {
	int maximum = 1, posmax = 0, pos = 0, len = 1;

	for (int i = 1; i < length; ++i) {
		if (sign(v[i - 1]) != sign(v[i])) {
			++len;
		}
		else {
			len = 1;
			pos = i;
		}
		if (len > maximum) {
			maximum = len;
			posmax = pos;
		}
	}
	Result r;
	r.start = v + posmax;
	r.length = maximum;
	return r;
}
