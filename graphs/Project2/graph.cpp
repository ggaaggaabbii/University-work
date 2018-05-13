#include "graph.h"

Graph::Graph()
{
}

Graph::Graph(int n)
{
    for (int i = 0; i < n; ++i) {
        nodes.insert(i);
    }
}

Graph::Graph(Graph& g)
{
    this->nodes = g.nodes;
    this->graphIn = g.graphIn;
    this->graphOut = g.graphOut;
    this->edgeIndex = g.edgeIndex;
}
Graph::~Graph()
{
}

std::unordered_set<int> Graph::parseX()
{
    return nodes;
}

std::unordered_set<int> Graph::parseNIn(int node)
{
    std::unordered_set<int> S;

    for (auto it : graphIn[node]) {
        S.insert(it.first);
    }

    return S;
}

std::unordered_set<int> Graph::parseNOut(int node)
{
    std::unordered_set<int> S;

    for (auto it : graphOut[node]) {
        S.insert(it.first);
    }

    return S;
}

bool Graph::addEdge(int source, int dest)
{
    if (isEdge(source, dest) != -1) {
        return false;
    }

    if (nodes.find(source) == nodes.end()) {
        return false;
    }

    if (nodes.find(dest) == nodes.end()) {
        return false;
    }

    graphIn[dest][source] = edgeIndex;
    graphOut[source][dest] = edgeIndex;
    edgeIndex++;
    return true;
}

bool Graph::addVertex(int node)
{
    if (nodes.find(node) != nodes.end()) {
        return false;
    }

    this->nodes.insert(node);
    return true;
}

int Graph::isEdge(int source, int dest)
{
    std::unordered_map<int, int>::const_iterator got = graphOut[source].find(dest);

    if (got != graphOut[source].end()) {
        return got->second;
    }

    return -1;
}

int Graph::getNumberOfVertices()
{
    return nodes.size();
}

int Graph::getInDegree(int node)
{
    if (nodes.find(node) != nodes.end()) {
        return graphIn[node].size();
    }

    return -1;
}

int Graph::getOutDegree(int node)
{
    if (nodes.find(node) != nodes.end()) {
        return graphOut[node].size();
    }

    return -1;
}

Graph& Graph::operator =(Graph& g)
{
    this->nodes = g.nodes;
    this->graphIn = g.graphIn;
    this->graphOut = g.graphOut;
    this->edgeIndex = g.edgeIndex;
    return *this;
}

std::unordered_set<int> Graph::getNodes()
{
    return nodes;
}

