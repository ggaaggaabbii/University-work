#ifndef SUPERHERO_H
#define SUPERHERO_H

#include "character.h"

class superhero: public character {

    public:
        superhero();
        superhero(std::string n, int h, int d);
        void strike(character& c) override {c.setHP(c.getHP() - this->dmg);}
};

#endif // SUPERHERO_H
