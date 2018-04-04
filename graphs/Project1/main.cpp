#include <bits/stdc++.h>
#include "graph.h"
#include "userinterface.h"
#include <assert.h>

void smallTest()
{
    Graph G(10);
    G.addEdge(1, 2, 3);
    G.addEdge(5, 3, 4);
    G.addEdge(9, 0, 1);
    G.addEdge(1, 9, 7);
    G.addEdge(0, 2, 0);
    G.addEdge(3, 4, 2);
    assert(G.isEdge(1, 2) == 0);
    assert(G.deleteEdge(1, 2));
    assert(G.isEdge(1, 2) == -1);
    G.deleteNode(3);
    G.addVertex(11);
    G.addEdge(11, 2, 1);
}

int main()
{
    //smallTest();
    std::string file;
    std::cout << "File:";
    std::getline(std::cin, file);
    UserInterface u(file);
    u.start();
    return 0;
}
