#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include "graph.h"
#include <bits/stdc++.h>

class UserInterface {
  private:
    std::string fileName;
    Graph G{0};
  public:
    UserInterface(std::string fi = "");
    void start();
    void printMenu();
    void printEdges();
    void checkEdge();
    void getInOutDegree();
    void printInbound();
    void printOutbound();
    void printEdge();
    void modifyEdge();
    void deleteEdge();
    void deleteVertex();
    void addVertex();
    void addEdge();
};

#endif // USERINTERFACE_H
