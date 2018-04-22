#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "controller.h"
#include "validator.h"
#include <bits/stdc++.h>

class UserInterface {
  private:
    Controller* ctrl;
    Validator* val;

  public:
    UserInterface(Controller*, Validator* );
    void start();
    void add();
    void printMenu();
    void genP();
    void genH();
    void printAll();
};

#endif // USERINTERFACE_H
