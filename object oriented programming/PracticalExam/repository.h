#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <bits/stdc++.h>
#include "participant.h"
#include "question.h"

class Repository {
    private:
        std::string fileQ;
        std::string fileP;
        std::vector <Participant>part;
        std::vector <Question>questions;

    public:
        Repository(std::string f1 = "", std::string f2 = "");
        void writeToFile();
        std::vector<Participant> getParticipants();
        std::vector<Question> getQuestions();
        int getScoreOfParticipant(const std::string&);
        void addQuestion(const Question&);
        void addPart(const Participant&);
        void answer(const std::string& name, int score);
};

#endif // REPOSITORY_H
