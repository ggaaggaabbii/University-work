#include "controller.h"

Controller::Controller(Repository* r)
{
    repo = r;
}

void Controller::add(Song& s)
{
    repo->add(s);
}

bool cmp(Song a, Song b)
{
    return a.getHe() < b.getHe();
}

std::vector<Song> Controller::getP(int dur)
{
    std::vector<Song> rez;
    std::vector<Song> s;
    Song son;

    for (auto it : repo->getList()) {
        son = it;
        s.push_back(son);
    }

    int sum = 0;

    for (int i = 0; i <= s.size(); ++i) {
        for (int j = i + 1; j <= s.size(); ++j) {
            if (s[j] < s[i]) {
                son = s[j];
                s[j] = s[i];
                s[i] = son;
            }
        }
    }

    for (auto it : s) {
        if (sum + it.getDur() <= dur) {
            rez.push_back(it);
            sum += it.getDur();
        }
    }

    return rez;
}

std::vector<Song> Controller::getAll()
{
    return repo->getList();
}

std::vector<Song> Controller::getH(int dur)
{
    std::vector<Song> rez;
    std::vector<Song> s;
    Song son;

    for (auto it : repo->getList()) {
        son = it;
        s.push_back(son);
    }

    int sum = 0;

    for (int i = 0; i <= s.size(); ++i) {
        for (int j = i + 1; j <= s.size(); ++j) {
            if (s[j] < s[i]) {
                son = s[j];
                s[j] = s[i];
                s[i] = son;
            }
        }
    }

    for (int i = s.size() - 1; i >= 0; --i) {
        if (sum + s[i].getDur() <= dur) {
            rez.push_back(s[i]);
            sum += s[i].getDur();
        }
    }

    return rez;
}
