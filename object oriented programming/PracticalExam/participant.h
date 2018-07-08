#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <bits/stdc++.h>

class Participant {
    private:
        std::string name;
        int score;

    public:
        Participant(const std::string&, int);
        Participant(const Participant&);
        std::string getName();
        int getScore();
        void increaseScore(int s);
};

#endif // PARTICIPANT_H
