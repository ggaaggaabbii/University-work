#ifndef CHARACTER_H
#define CHARACTER_H

#include<bits/stdc++.h>

class character {
    protected:
        std::string name;
        int dmg;
        int hp;


    public:
        std::string type;
        character() {}
        character(std::string n, int h, int d): name{n}, dmg{d}, hp{h} {}
        int getDmg() {return dmg;}
        int getHP() {return hp;}
        std::string getName() {return name;}
        void setDMG(int dmg) {this->dmg = dmg;}
        void setHP(int hp) {this->hp = hp;}
        virtual void strike(character&) = 0;
        //virtual copy(character*) = 0;
};

#endif // CHARACTER_H
