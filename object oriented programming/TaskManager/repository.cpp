#include "repository.h"

Repository::Repository(const std::string& file)
{
    if (file == "") {
        return;
    }

    std::ifstream f(file);
    std::string name;
    std::string id;
    std::string line;
    bool ok = true;

    while (std::getline(f, line)) {

        for (auto c : line) {
            if (c == ',') {
                ok = false;
                continue;
            }

            if (ok) {
                name.push_back(c);

            } else {
                id.push_back(c);
            }
        }

        progs.push_back(Programmer{name, std::stoi(id)});
        ok = true;
        id = "";
        name = "";
    }

    std::ifstream g("tasks.txt");
    std::string desc;
    std::string idt;
    std::string status;
    bool ok1 = true;
    bool ok2 = true;

    while (std::getline(g, line)) {

        for (auto c : line) {
            if (c == ',') {
                if (ok1) {
                    ok1 = false;

                } else {
                    ok2 = false;
                }

                continue;
            }

            if (ok1) {
                desc.push_back(c);

            } else if (ok2) {
                status.push_back(c);

            } else {
                idt.push_back(c);
            }
        }

        tasks.push_back(Task{desc, std::stoi(idt), std::stoi(status)});
        ok1 = true;
        ok2 = true;
        status = "";
        idt = "";
        desc = "";
    }

    g.close();
    f.close();
}

Repository::Repository()
{

}
Repository::~Repository()
{

}

