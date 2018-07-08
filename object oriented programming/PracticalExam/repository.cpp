#include "repository.h"

Repository::Repository(std::string f1, std::string f2)
{
    if (f1 == "") {
        return;
    }

    fileQ = f1;
    fileP = f2;

    std::ifstream f(f1);
    std::string line;
    std::string id;
    std::string text;
    std::string ans;
    std::string score;

    while (std::getline(f, line)) {
        id = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        text = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        ans = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        score = line.substr(0, line.find(","));
        questions.push_back(Question{std::stoi(id), text, ans, std::stoi(score)});
    }

    f.close();

    std::ifstream fin(f2);

    while (std::getline(fin, line)) {
        text = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        score = line.substr(0, line.find(","));
        part.push_back(Participant{text, std::stoi(score)});
    }

    fin.close();
}

void Repository::writeToFile()
{
    std::ofstream g(fileQ);

    for (auto it : questions) {
        g << it.getStr() << "\n";
    }

    g.close();
}

std::vector<Participant> Repository::getParticipants()
{
    return part;
}

std::vector<Question> Repository::getQuestions()
{
    return questions;
}

int Repository::getScoreOfParticipant(const std::string& s)
{
    for (auto it : part) {
        if (it.getName() == s) {
            return it.getScore();
        }
    }
}

void Repository::addQuestion(const Question& q)
{
    questions.push_back(q);
    writeToFile();
}

void Repository::addPart(const Participant& p)
{
    part.push_back(p);
}

void Repository::answer(const std::string& name, int score)
{
    for (int i = 0; i < part.size(); ++i) {
        if (part[i].getName() == name) {
            part[i].increaseScore(score);
            return;
        }
    }
}
