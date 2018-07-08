#include "participant.h"

Participant::Participant(const std::string& n, int p): name{n}, points{p}
{

}

Participant::Participant(const Participant& other): name{other.name}, points{other.points}
{

}
