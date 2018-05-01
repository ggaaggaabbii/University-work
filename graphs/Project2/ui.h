#ifndef UI_H
#define UI_H

#include <bits/stdc++.h>
#include "graph.h"
#include "solvefunctions.h"
#include "configuration.h"
#include <boost/multiprecision/cpp_int.hpp>

using namespace boost::multiprecision;

class ui {
  public:
    ui();
    void start();
    void printMenu();
    void conComp();
    void readGraphUndir(std::string, Graph&);
    void readGraphDir(std::string, Graph&);
    void strConComp();
    void biConComp();
    void WGC();
    void Puzzle15();
};

#endif // UI_H
