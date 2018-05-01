#ifndef SOLVEFUNCTIONS_H
#define SOLVEFUNCTIONS_H

#include <bits/stdc++.h>
#include <bits/stl_algo.h>
#include "graph.h"
#include "configuration.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

/*
determines a map that gives the component of each vertex
input: a graph
output: the result map
*/
std::unordered_map<int, int> connectedComp(Graph&);
/*
performes a breath first search for a given vertex, and assigns the index of the initial node to all the vertices in the component
input: a graph, the initial vertex, a reference to the map of components
*/
void bfs(Graph&, int, std::unordered_map<int, int>&);
/*
determines the strongly connected components and maps each vertex to the coresponding component
input: a graph
output: the result map
*/
std::unordered_map<int, int> stronglyConnectedComponents(Graph& g);
/*
the depth first search used to solve the strongly connected components
input: a grapf, the current node, the map of nodes and components, the index of each node, a boolean to check if the node is on the stack,
       the current index, the stack, the index of the current strongly connected component
*/
void dfs(Graph&, int, std::unordered_map<int, int>&, std::unordered_map<int, int>&, bool*, int&,
         std::stack<int>&, int&);

/*
determines the biconnected components
input: a graph
output: a vector containing the lists of nodes in each component
*/
std::vector<std::vector<int> >biconnectedComponents(Graph& g);

/*
dfs used to determine the biconnected components
input: a reference to the graph, the current node, the current level, the visited array, the nivel of the components,
       the lowest component that each node has access to, the edge stack, the result vector
*/
void dfs2(Graph&, int, int, bool*, std::unordered_map<int, int>&, std::unordered_map<int, int>&,
          std::stack<std::pair<int, int> >&, std::vector<std::vector<int> >& );

/*
solves the wolf goat cabbage problem
output: returns a vector of states representing the way from the initial problem to the result
        the states are encoded as follows: WGCB - where W, G, C, B take values from 0 to 1, 0 - left side of the lake, 1 - right side of the lake
*/
std::vector<int> wolfGoatCabbageProblem();

/*
solves the 15 puzzle
input: the initial configuration of the matrix
output: a list of configurations going from the initial configuration to the solution
*/
std::vector<configuration> solve15Puzzle(configuration);
#endif // SOLVEFUNCTIONS_H
