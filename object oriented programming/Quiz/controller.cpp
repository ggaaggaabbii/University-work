#include "controller.h"

Controller::Controller(const Repository& r, QWidget* parent) : repo{r}, QWidget(parent)
{

}

std::vector<Questions> Controller::getQuestions()
{
    return repo.getQuestions();
}

std::vector<Questions> Controller::getSorted()
{
    std::vector<Questions>v = repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Questions & a, Questions & b) {return a.getPoint() > b.getPoint();});
    return v;
}

void Controller::addQuestion(std::string id, std::string text, std::string ans, std::string points)
{
    if (id == "" || text == "" || ans == "" || points == "") {
        throw std::runtime_error{"empty"};
    }

    int i = std::stoi(id);

    for (auto it : repo.getQuestions()) {
        if (it.getId() == i) {
            throw std::runtime_error{"invalid id"};
        }
    }

    repo.addQuestion(Questions{i, text, ans, std::stoi(points)});
    emit updatedRepo();
}

int Controller::getScoreOfPart(std::string name)
{
    for (auto it : repo.getParticipants()) {
        if (it.getName() == name) {
            return it.getScore();
        }
    }
}

std::string Controller::getQueFromIndex(int line)
{
    std::vector<Questions>v = repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Questions & a, Questions & b) {return a.getPoint() > b.getPoint();});
    return v[line].getStr();
}

void Controller::answer(int line, std::string name, std::string ans)
{
    std::vector<Questions>v = repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Questions & a, Questions & b) {return a.getPoint() > b.getPoint();});

    if (v[line].getAns() == ans) {
        repo.answer(name, v[line].getPoint());
    }
}
