#ifndef GOD_H
#define GOD_H

#include "character.h"
#include "timeline.h"

class god: public character {

    private:
        //timeline time;

    public:
        god(std::string name, int hp, int dmg);
        void strike(character& c) override {c.setHP(c.getHP() - this->dmg);}
        //void copy(character*);

};

#endif // GOD_H
