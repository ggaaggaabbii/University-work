#ifndef BATTLE_H
#define BATTLE_H

#include "character.h"
#include "superhero.h"
#include "god.h"
#include <bits/stdc++.h>

class battle {
    private:
        std::vector<character*> bat;
    public:
        battle();
        ~battle();
        void add(character*);
        std::vector<character*> getList();
        void operator = (battle);
        void del(std::string);
};

#endif // BATTLE_H
