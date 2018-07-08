#ifndef QUESTION_H
#define QUESTION_H

#include <bits/stdc++.h>

class Question {
    private:
        int id;
        std::string text;
        std::string ans;
        int score;
    public:
        Question(int, const std::string&, const std::string&, int);
        Question(const Question&);
        std::string getStr();
        std::string getStrParticipant();
        int getId();
        int getScore();
        std::string getAns();

};

#endif // QUESTION_H
