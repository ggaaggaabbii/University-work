#include "participant.h"

Participant::Participant(const std::string& n, int p): name{n}, score{p}
{

}

Participant::Participant(const Participant& p): name{p.name}, score{p.score}
{

}

std::string Participant::getName()
{
    return name;
}

int Participant::getScore()
{
    return score;
}

void Participant::increaseScore(int s)
{
    score += s;
}
