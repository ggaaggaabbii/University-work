#include "ui.h"

ui::ui()
{

}

void printMenu()
{
    std::cout << "0. Exit\n";
    std::cout << "1. Add\n";
    std::cout << "2. Show\n";
    std::cout << "3. print\n";
    std::cout << "4. strike\n";
}

void ui::start()
{
    std::string cmd;

    while (true) {
        printMenu();
        std::getline(std::cin, cmd);

        if (cmd == "0") {
            break;

        } else if (cmd == "1") {
            add();

        } else if (cmd == "2") {
            show();

        } else if (cmd == "3") {
            showF();

        } else if (cmd == "4") {
            strike();
        }
    }
}

void ui::add()
{
    std::string type;
    std::string name;
    int hp;
    int dmg;

    std::cout << "type: g/s\n";
    std::getline(std::cin, type);
    std::getline(std::cin, name);
    std::cin >> hp;
    std::cin >> dmg;
    ctrl.add(type, name, hp, dmg);
    std::cin.get();
}

void ui::show()
{
    for (auto it : ctrl.getList()) {
        std::cout << it->getName() << " " << it->getHP() << " " << it->getDmg() << "\n";
    }
}

void ui::showF()
{
    std::ofstream f("output.txt");

    for (auto it : ctrl.getList()) {
        f << it->getName() << " " << it->getHP() << " " << it->getDmg() << "\n";
    }

    f.close();
}

void ui::strike()
{
    std::string n1, n2;
    std::getline(std::cin, n1);
    std::getline(std::cin, n2);

    ctrl.strike(n1, n2);

}
