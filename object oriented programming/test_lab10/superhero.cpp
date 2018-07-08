#include "superhero.h"

superhero::superhero()
{

}

superhero::superhero(std::string name, int hp, int dmg)
{
    this->dmg = dmg;
    this->name = name;
    this->hp = hp;
    this->type = "s";
}

