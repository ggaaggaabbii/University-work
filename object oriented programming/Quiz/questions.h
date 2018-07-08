#ifndef QUESTIONS_H
#define QUESTIONS_H

#include <bits/stdc++.h>

class Questions {
    private:
        std::string text;
        std::string ans;
        int id;
        int points;
    public:
        Questions(int id, const std::string& t, const std::string& a, int p);
        Questions(const Questions& other);
        int getId();
        std::string getText();
        std::string getAns();
        int getPoint();
        std::string getStr();
        std::string getPartStr();
};

#endif // QUESTIONS_H
