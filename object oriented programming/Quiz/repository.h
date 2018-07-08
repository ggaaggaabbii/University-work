#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <bits/stdc++.h>
#include "questions.h"
#include "participant.h"

class Repository {
    private:
        std::vector<Questions> quiz;
        std::vector<Participant> part;
        std::string fi;
        std::string f2;
    public:
        Repository();
        Repository(const std::string& file, const std::string& file2);
        void writeToFile();
        std::vector<Participant> getParticipants();
        std::vector<Questions> getQuestions();
        void addQuestion(const Questions& q);
        void answer(std::string name, int score);
};

#endif // REPOSITORY_H
