#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <bits/stdc++.h>

class Participant {
    private:
        std::string name;
        int points;
    public:
        Participant(const std::string& n, int p);
        Participant(const Participant& other);
        std::string getName() {
            return name;
        }
        int getScore() {
            return points;
        }
        void increaseScore(int score) {
            points += score;
        }
};

#endif // PARTICIPANT_H
