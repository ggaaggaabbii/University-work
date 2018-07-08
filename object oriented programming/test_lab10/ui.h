#ifndef UI_H
#define UI_H

#include "controller.h"
#include <bits/stdc++.h>

class ui {
    private:
        controller ctrl;
    public:
        ui();
        void start();
        void add();
        void show();
        void showF();
        void strike();
};

#endif // UI_H
