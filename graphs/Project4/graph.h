#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
#include "edgeproperty.h"

class Graph {
    private:
        std::unordered_set<int> nodes;
        std::unordered_map<int, std::unordered_map<int, int> > graphIn;
        std::unordered_map<int, std::unordered_map<int, int> > graphOut;
        int edgeIndex = 0;
        EdgeProperty<int> EP;

    public:
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
        bool addEdge(int, int, int);
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
        prints the graph
        */
        void printGraph();
        /*
        delets an edge
        input: the ednpoints of the edge
        output: true if the edge could be deleted, false otherwise
        */
        bool deleteEdge(int, int);
        /*
        deletes a vertex and the associated edges
        input: the edge id
        output: true if the node could be deleted, false otherwise
        */
        bool deleteNode(int);
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
        /*
        returns an edge by id with the associated endpoints and cost
        */
        std::tuple<int, int, int> getEdge(int);
        /*
        updates the cost of an edge
        */
        bool updateEdge(int, int);

        int getCost(int x, int y);
};

#endif // GRAPH_H
