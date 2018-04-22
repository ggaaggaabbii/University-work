#include "song.h"

Song::Song()
{
}

Song::Song(int i, std::string t, std::string a, int d, double h)
{
    id = i;
    title = t;
    artist = a;
    duration = d;
    heaviness = h;
}

Song& Song::operator=(Song& s)
{
    this->id = s.getId();
    this->title = s.getTitle();
    this->artist = s.getArtist();
    this->duration = s.getDur();
    this->heaviness = s.getHe();
    return *this;
}

int Song::getId()
{
    return id;
}

std::string Song::getTitle()
{
    return title;
}

std::string Song::getArtist()
{
    return artist;
}

int Song::getDur()
{
    return duration;
}

double Song::getHe()
{
    return heaviness;
}

std::string Song::toStr()
{
    std::string s = "";
    return s;
}

