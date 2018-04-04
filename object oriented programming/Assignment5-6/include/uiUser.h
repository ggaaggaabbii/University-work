#ifndef UIUSER_H
#define UIUSER_H

#include <bits/stdc++.h>
#include "Controller.h"
#include "DynamicVector.h"

class uiUser {

  private:
    Controller* ctrl;


  public:
    uiUser(Controller& c): ctrl{&c} {}
    void start();
    void printMovies();
    void printMenu();
    void printSubmenu();
    void printWatchList();
    void removeFromWatchList();
};

#endif // UIUSER_H
