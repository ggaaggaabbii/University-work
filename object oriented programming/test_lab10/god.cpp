#include "god.h"

god::god(std::string name, int hp, int dmg)
{
    this->dmg = dmg;
    this->name = name;
    this->hp = hp;
    this->type = "g";
    //time = t;
}

/*
void god::copy(character* c)
{
    this->getDmg() = c->getDmg();
    this->getHP() = c->getHP();
    this->getName() = c->getName();
}
*/
