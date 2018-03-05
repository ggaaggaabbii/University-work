#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int *start, length;
} Result;

double power(double x, int n);
Result subsequence(int *v, int length);