#include "repository.h"

Repository::Repository()
{

}

Repository::Repository(const std::string& file, const std::string& file2)
{
    fi = file;
    f2 = file2;

    if (file == "") {
        return;
    }

    std::ifstream f(file);
    std::string line;
    std::string id;
    std::string text;
    std::string ans;
    std::string points;

    while (std::getline(f, line)) {
        id = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        text = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        ans = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        points = line.substr(0, line.find(","));
        quiz.push_back(Questions{std::stoi(id), text, ans, std::stoi(points)});
    }

    f.close();
    std::ifstream fin(f2);

    while (std::getline(fin, line)) {
        text = line.substr(0, line.find(","));
        line = line.substr(line.find(",") + 1, line.size());
        points = line.substr(0, line.find(","));
        part.push_back(Participant{text, std::stoi(points)});
    }

    fin.close();
}

void Repository::writeToFile()
{
    if (fi == "") {
        return;
    }

    std::ofstream g(fi);

    for (auto it : quiz) {
        g << it.getId() << "," << it.getText() << "," << it.getAns() << "," << it.getPoint() << "\n";
    }

    g.close();
}

std::vector<Participant> Repository::getParticipants()
{
    return part;
}

std::vector<Questions> Repository::getQuestions()
{
    return quiz;
}

void Repository::addQuestion(const Questions& q)
{
    quiz.push_back(q);
    writeToFile();
}

void Repository::answer(std::string name, int score)
{
    for (int i = 0; i < part.size(); ++i) {
        if (part[i].getName() == name) {
            part[i].increaseScore(score);
        }
    }
}
