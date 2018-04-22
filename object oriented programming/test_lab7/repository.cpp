#include "repository.h"

Repository::Repository()
{
}

void Repository::add(Song& s)
{
    if (!find(s)) {
        elems.push_back(s);
        return;
    }

    throw std::string{"Song already in the list"};
}

bool Repository::find(Song& s)
{
    for (auto it : elems) {
        if (it.getId() == s.getId()) {
            return true;
        }
    }

    return false;
}

std::vector<Song> Repository::getList()
{
    return elems;
}
