#include "userinterface.h"

UserInterface::UserInterface(Controller* c, Validator* v)
{
    ctrl = c;
    val = v;
}

void UserInterface::start()
{
    std::string cmd;

    while (1) {
        try {
            printMenu();
            std::getline(std::cin, cmd);

            if (cmd == "0") {
                return;
            } else if (cmd == "1") {
                add();
            } else if (cmd == "2") {
                genP();
            } else if (cmd == "3") {
                genH();
            } else if (cmd == "4") {
                printAll();
            } else {
                std::cout << "Invalid command\n";
            }
        } catch (std::string& s) {
            std::cout << s << '\n';
        }
    }
}

void UserInterface::add()
{
    std::string i, t, a, d, h;
    std::cout << "id:";
    std::getline(std::cin, i);
    std::cout << "title:";
    std::getline(std::cin, t);
    std::cout << "artist:";
    std::getline(std::cin, a);
    std::cout << "duartion:";
    std::getline(std::cin, d);
    std::cout << "heaviness:";
    std::getline(std::cin, h);

    if (val->validate(i, t, a, d, h)) {
        Song s{atoi(i.c_str()), t, a, atoi(d.c_str()), atof(h.c_str())};
        ctrl->add(s);
    }
}

void UserInterface::printMenu()
{
    std::cout << "0. Exit\n";
    std::cout << "1. Add\n";
    std::cout << "2. Gen playlist\n";
    std::cout << "3. HEAVY\n";
    std::cout << "4. Print all\n";
}

void UserInterface::genP()
{
    std::string s;
    std::cout << "dur:";
    std::getline(std::cin, s);

    if (val->isInt(s)) {
    } else {
        std::cout << "Invalid duration";
    }

    for (auto it : ctrl->getP(atoi(s.c_str()))) {
        std::cout << it.getTitle() << "\n";
    }
}

void UserInterface::genH()
{
    std::string s;
    std::cout << "dur:";
    std::getline(std::cin, s);

    if (val->isInt(s)) {
    } else {
        std::cout << "Invalid duration";
    }

    for (auto it : ctrl->getH(atoi(s.c_str()))) {
        std::cout << it.getTitle() << "\n";
    }
}

void UserInterface::printAll()
{
    std::vector<Song>l = ctrl->getAll();

    for (auto it : l) {
        std::cout << it.getId() << "\n" << it.getTitle() << "\n" << it.getArtist() << "\n" << it.getDur() <<
                  "\n" << it.getHe() << "\n\n";
    }
}
