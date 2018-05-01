#include <bits/stdc++.h>
#include "graph.h"
#include "solvefunctions.h"
#include "ui.h"

void smallTest()
{
    Graph G(10);
    G.addEdge(1, 2);
    G.addEdge(5, 3);
    G.addEdge(9, 0);
    G.addEdge(1, 9);
    G.addEdge(0, 2);
    G.addEdge(3, 4);
    assert(G.isEdge(1, 2) == 0);
    G.addVertex(11);
    G.addEdge(11, 2);
    assert(G.isEdge(11, 2));
    std::unordered_map<int, int> rez = connectedComp(G);
}

int main()
{
    //smallTest();
    ui u;
    u.start();
    return 0;
}
