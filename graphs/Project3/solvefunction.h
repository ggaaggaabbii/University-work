#ifndef SOLVEFUNCTION_H
#define SOLVEFUNCTION_H

#include "graph.h"
#include <bits/stdc++.h>

int lowestLengthWalk(Graph& g, int source, int dest);
int numberOfDistinctMinimumCostWalks(Graph& g, int source, int dest);
int numberOfDistinctWalks(Graph& g, int source, int dest);
void bridgeAndTorchProblem(std::vector<int>& people);

#endif // SOLVEFUNCTION_H
