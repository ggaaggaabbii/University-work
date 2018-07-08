#include "controller.h"

Controller::Controller(const Repository& r, QWidget* parent) : repo{r}, QWidget(parent)
{

}

std::vector<Question> Controller::getQuestions()
{
    std::vector<Question>v =  repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Question & a, Question & b) {return a.getId() < b.getId();});
    return v;
}

int Controller::getScoreOfParticipant(const std::string& s)
{
    return repo.getScoreOfParticipant(s);
}

std::vector<Question> Controller::getQuestionsSorted()
{
    std::vector<Question>v =  repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Question & a, Question & b) {return a.getScore() > b.getScore();});
    return v;
}

void Controller::addQuestion(const std::string& id, const std::string& text, const std::string& ans,
                             const std::string& score)
{
    if (id == "" || text == "" || ans == "" || score == "") {
        throw std::runtime_error{"Empty slot"};
    }

    std::vector<Question>v = repo.getQuestions();

    for (auto it : v) {
        if (it.getId() == std::stoi(id)) {
            throw std::runtime_error{"Id already in the list"};
        }
    }

    repo.addQuestion(Question{std::stoi(id), text, ans, std::stoi(score)});
    emit updateList();
}

void Controller::answer(int line, const std::string& name, const std::string& ans)
{
    std::vector<Question>v = repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Question & a, Question & b) {return a.getScore() > b.getScore();});

    if (v[line].getAns() == ans) {
        repo.answer(name, v[line].getScore());
    }

    emit scoreUpdate();
}

std::string Controller::getQuestionFromRow(int l)
{
    std::vector<Question>v = repo.getQuestions();
    std::sort(v.begin(), v.end(), [](Question & a, Question & b) {return a.getScore() > b.getScore();});
    return v[l].getStr();
}
