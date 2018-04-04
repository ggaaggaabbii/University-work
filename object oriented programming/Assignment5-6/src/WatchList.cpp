#include "../include/WatchList.h"

WatchList::WatchList()
{
}

bool WatchList::addToWatchList(Movie M)
{
    if (find(M.getTitle(), M.getReleaseDate()) == -1) {
        toWatch.addElement(M);
        return true;
    }

    return false;
}

int WatchList::find(std::string title, std::string releaseDate)
{
    int pos = 0;

    for (auto it : toWatch) {
        if (it.getTitle() == title && it.getReleaseDate() == releaseDate) {
            return pos;
        }

        ++pos;
    }

    return -1;
}

DynamicVector<Movie>& WatchList::getList()
{
    return toWatch;
}

bool WatchList::removeFromWatchList(std::string& title, std::string& releaseDate)
{
    int pos = find(title, releaseDate);

    if (pos == -1) {
        return false;
    }

    toWatch = toWatch - toWatch[pos];
    return true;
}


