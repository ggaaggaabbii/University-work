#ifndef SOLVER_H
#define SOLVER_H
#include <bits/stdc++.h>
#include "graph.h"
#include "edgeproperty.h"
#define INF 1000000000

bool isDAG(Graph& g);
std::unordered_map<std::string, std::unordered_map<int, int>> scheduler(Graph&,
                                                                        std::unordered_map<int, int>&);
std::vector<int> getCritic(std::unordered_map < std::string, std::unordered_map<int, int>>&,
                           Graph&);
int nOPaths(Graph&, int, int);
int nOMinPaths(Graph&, int, int);

/*
parse the preorder list
if a comes before b in pre list and b comes before a in post list then b is a child of a
else we move upwords with a
*/
void buildTreeFromPrePost(Graph&, std::vector<int>&, std::vector<int>&);

#endif // SOLVER_H
