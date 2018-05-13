#include "graph.h"

Graph::Graph(int n)
{
    for (int i = 0; i < n; ++i) {
        this->nodes.insert(i);
    }
}

Graph::Graph(Graph& g)
{
    this->nodes = g.nodes;
    this->graphIn = g.graphIn;
    this->graphOut = g.graphOut;
    this->edgeIndex = g.edgeIndex;
    this->EP = g.EP;
}
Graph::~Graph()
{
}

std::unordered_set<int> Graph::parseX()
{
    return this->nodes;
}

std::unordered_set<int> Graph::parseNIn(int node)
{
    std::unordered_set<int> S;

    for (auto it : this->graphIn[node]) {
        S.insert(it.first);
    }

    return S;
}

std::unordered_set<int> Graph::parseNOut(int node)
{
    std::unordered_set<int> S;

    for (auto it : this->graphOut[node]) {
        S.insert(it.first);
    }

    return S;
}

bool Graph::addEdge(int source, int dest, int cost)
{
    if (isEdge(source, dest) != -1) {
        return false;
    }

    if (this->nodes.find(source) == this->nodes.end()) {
        return false;
    }

    if (this->nodes.find(dest) == this->nodes.end()) {
        return false;
    }

    this->graphIn[dest][source] = this->edgeIndex;
    this->graphOut[source][dest] = this->edgeIndex;
    this->EP.addEdge(this->edgeIndex, source, dest, cost);
    this->edgeIndex++;
    return true;
}

bool Graph::addVertex(int node)
{
    if (this->nodes.find(node) != this->nodes.end()) {
        return false;
    }

    this->nodes.insert(node);
    return true;
}

int Graph::isEdge(int source, int dest)
{
    std::unordered_map<int, int>::const_iterator got = this->graphOut[source].find(dest);

    if (got != this->graphOut[source].end()) {
        return got->second;
    }

    return -1;
}

void Graph::printGraph()
{
    for (auto it : parseX()) {
        std::cout << it << ": ";

        for (auto it2 : parseNIn(it)) {
            std::cout << it2 << " ";
        }

        std::cout << "| ";

        for (auto it2 : parseNOut(it)) {
            std::cout << it2 << " ";
        }

        std::cout << "\n";
    }
}

bool Graph::deleteEdge(int source, int dest)
{
    if (isEdge(source, dest) == -1) {
        return false;
    }

    this->EP.deleteEdge(this->graphIn[dest][source]);
    this->graphIn[dest].erase(source);
    this->graphOut[source].erase(dest);
    return true;
}

bool Graph::deleteNode(int node)
{
    if (this->nodes.find(node) == this->nodes.end()) {
        return false;
    }

    this->nodes.erase(node);

    for (auto it : this->graphOut[node]) {
        this->EP.deleteEdge(this->graphIn[it.first][node]);
        this->graphIn[it.first].erase(node);
    }

    for (auto it : this->graphIn[node]) {
        this->graphOut[it.first].erase(node);
    }

    this->graphIn.erase(node);
    this->graphOut.erase(node);
    return true;
}

int Graph::getNumberOfVertices()
{
    return this->nodes.size();
}

int Graph::getInDegree(int node)
{
    if (this->nodes.find(node) != this->nodes.end()) {
        return this->graphIn[node].size();
    }

    return -1;
}

int Graph::getOutDegree(int node)
{
    if (this->nodes.find(node) != this->nodes.end()) {
        return this->graphOut[node].size();
    }

    return -1;
}

Graph& Graph::operator =(Graph& g)
{
    this->nodes = g.nodes;
    this->graphIn = g.graphIn;
    this->graphOut = g.graphOut;
    this->edgeIndex = g.edgeIndex;
    this->EP = g.EP;
    return *this;
}

std::unordered_set<int> Graph::getNodes()
{
    return this->nodes;
}

std::tuple<int, int, int> Graph::getEdge(int edge)
{
    return EP.getEdge(edge);
}

bool Graph::updateEdge(int edge, int newVal)
{
    return EP.updateEdge(edge, newVal);
}

