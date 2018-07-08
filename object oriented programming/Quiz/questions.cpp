#include "questions.h"

Questions::Questions(int i, const std::string& t, const std::string& a, int p): id{i}, text{t}, ans{a},
    points{p}
{

}

Questions::Questions(const Questions& other): id{other.id}, text{other.text}, ans{other.ans}, points{other.points}
{

}

int Questions::getId()
{
    return id;
}

std::string Questions::getText()
{
    return text;
}

std::string Questions::getAns()
{
    return ans;
}

int Questions::getPoint()
{
    return points;
}

std::string Questions::getStr()
{
    return std::to_string(id) + ", " + text + ", " + ans + ", " + std::to_string(points);
}

std::string Questions::getPartStr()
{
    return std::to_string(id) + ", " + text + ", " + std::to_string(points);
}
