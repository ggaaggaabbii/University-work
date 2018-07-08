#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "battle.h"
#include "character.h"
#include "timeline.h"
#include "god.h"
#include "superhero.h"
#include <bits/stdc++.h>

class controller {
    private:
        battle bat;
        //timeline time;

    public:
        controller();
        void add(std::string type, std::string name, int hp, int dmg);
        std::vector<character*> getList();
        void undo();
        void strike(std::string, std::string);
};

#endif // CONTROLLER_H
