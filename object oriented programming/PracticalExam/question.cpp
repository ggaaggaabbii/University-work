#include "question.h"

Question::Question(int i, const std::string& t, const std::string& a, int s): id{i}, text{t}, ans{a},
    score{s}
{

}

Question::Question(const Question& q): id{q.id}, text{q.text}, ans{q.ans}, score{q.score}
{

}

std::string Question::getStr()
{
    return std::to_string(id) + "," + text + "," + ans + "," + std::to_string(score);
}

std::string Question::getStrParticipant()
{
    return std::to_string(id) + "," + text + "," + std::to_string(score);
}

int Question::getId()
{
    return id;
}

int Question::getScore()
{
    return score;
}

std::string Question::getAns()
{
    return ans;
}
