#include "battle.h"

battle::battle()
{

}

battle::~battle()
{
    for (auto it : bat) {
        delete it;
    }
}

void battle::add(character* c)
{
    for (auto it : bat) {
        if (it->getName() == c->getName()) {
            delete c;
            return;
        }
    }

    bat.push_back(c);
}

std::vector<character*> battle::getList()
{
    return bat;
}

void battle::operator =(battle b)
{
    this->bat = b.getList();

    for (int i = 0; i < bat.size(); ++i) {
        if (bat[i]->type == "s") {
            character* c = new superhero{bat[i]->getName(), bat[i]->getHP(), bat[i]->getDmg()};
            bat[i] = c;
        }
    }
}

void battle::del(std::string s)
{
    for (int i = 0; i < bat.size(); ++i) {
        if (bat[i]->getName() == s) {
            std::swap(bat[i], bat[bat.size()]);
            delete bat[bat.size()];
            bat.pop_back();
        }
    }
}

