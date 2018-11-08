#pragma once
#include <bits/stdc++.h>
#include "Controller.h"

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
