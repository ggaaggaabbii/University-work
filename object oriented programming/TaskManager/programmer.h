#ifndef PROGRAMMER_H
#define PROGRAMMER_H
#include <bits/stdc++.h>

class Programmer {
    private:
        std::string name;
        int id;
    public:
        Programmer();
        Programmer(const std::string& n, int i): name{n}, id{i} {}
        std::string getName() {return name;}
        int getId() {return id;}
};

#endif // PROGRAMMER_H
