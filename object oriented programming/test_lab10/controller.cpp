#include "controller.h"

controller::controller()
{
    add("s", "batman", 10, 20);
    add("s", "superman", 15, 10);
}

void controller::add(std::string type, std::string name, int hp, int dmg)
{
    if (type == "s") {
        character* c = new superhero{name, hp, dmg};
        bat.add(c);

    } else {
        character* c = new god{name, hp, dmg};
        bat.add(c);
    }
}

std::vector<character*> controller::getList()
{
    return bat.getList();
}

void controller::undo()
{
    /*
    if (time.getTimes()) {
        bat = time.getCurrent();
    }
    */
}

void controller::strike(std::string n1, std::string n2)
{
    std::vector<character*>v = bat.getList();

    character* c1;
    character* c2;

    for (int i = 0; i < v.size(); ++i) {
        if (v[i]->getName() == n1) {
            c1 = v[i];
        }

        if (v[i]->getName() == n2) {
            c2 = v[i];
        }
    }

    c1->strike(*c2);

    if (c2->getHP() <= 0) {
        bat.del(c2->getName());
    }
}




