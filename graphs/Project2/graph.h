#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;
class Graph {
  private:
    std::unordered_set<int> nodes;
    std::unordered_map<int, std::unordered_map<int, int> > graphIn;
    std::unordered_map<int, std::unordered_map<int, int> > graphOut;
    int edgeIndex = 0;

  public:
    Graph();
    Graph(int);
    /*
    the copy constructor
    */
    Graph(Graph&);
    ~Graph();
    /*
    returns an iterable containing the current vertices of the graph
    */
    std::unordered_set<int> parseX();
    /*
    returns an iterable containing the inbound neighbours of a vertex
    input: the vertex id
    */
    std::unordered_set<int> parseNIn(int);
    /*
    returns an iterable containing the outbound neighbours of a vertex
    input: the vertex id
    */
    std::unordered_set<int> parseNOut(int);
    /*
    adds an edge to the graph
    input: the endpoints of the edge and the cost
    output: true if the edge could be added, false otherwise
    */
    bool addEdge(int, int);
    /*
    adds a vertex to the graph
    input: the id of the vertex
    output: true if the vertex could be added, false otherwise
    */
    bool addVertex(int);
    /*
    checks if an edge exists
    input: the endpoints of the edge
    output: the id of the edge, or -1 if it doesn't exist
    */
    int isEdge(int, int);
    /*
     returns the number of vertices
    */
    int getNumberOfVertices();
    /*
    returns the in degree of a given node
    */
    int getInDegree(int);
    /*
    returns the out degree of a given node
    */
    int getOutDegree(int);
    /*
    operator = is used to make the graph copyable
    */
    Graph& operator =(Graph&);
    /*
    returns an iterable containing all the vertex ids
    */
    std::unordered_set<int> getNodes();

};

#endif // GRAPH_H
