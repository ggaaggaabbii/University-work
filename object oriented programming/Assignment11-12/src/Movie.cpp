#include "../include/Movie.h"

std::string Movie::getTitle() const
{
    return this->title;
}

std::string Movie::getGenre() const
{
    return this->genre;
}
std::string Movie::getReleaseDate() const
{
    return this->releaseDate;
}

long long Movie::getNumberOfLikes() const
{
    return this->numberOfLikes;
}

std::string Movie::getLink() const
{
    return this->linkOfTrailer;
}

Movie::~Movie()
{
}

Movie::Movie(const Movie& M)
{
    this->title = M.getTitle();
    this->genre = M.getGenre();
    this->releaseDate = M.getReleaseDate();
    this->numberOfLikes = M.getNumberOfLikes();
    this->linkOfTrailer = M.getLink();
}

void Movie::setTitle(const std::string& T)
{
    this->title = T;
}

void Movie::setGenre(const std::string& G)
{
    this->genre = G;
}

void Movie::setReleaseDate(const std::string& R)
{
    this->releaseDate = R;
}

void Movie::setNumbersOfLikes(const long long nr)
{
    this->numberOfLikes = nr;
}

void Movie::setLink(const std::string& L)
{
    this->linkOfTrailer = L;
}

bool Movie::operator==(const Movie& M)
{
    return this->title == M.getTitle() && this->genre == M.getGenre() &&
           this->releaseDate == M.getReleaseDate() &&
           this->numberOfLikes == M.getNumberOfLikes();
}

bool Movie::operator!=(const Movie& M)
{
    return this->title != M.getTitle() || this->genre != M.getGenre() ||
           this->releaseDate != M.getReleaseDate() ||
           this->numberOfLikes != M.getNumberOfLikes();
}

std::string Movie::computeString()
{
    std::string s = "";
    s += this->title;
    s += ";";
    s += this->genre;
    s += ";";
    s += this->releaseDate;
    s += ";";
    s += std::to_string(this->numberOfLikes);
    s += ";";
    s += this->linkOfTrailer;
    s += "\n";
    return s;
}

std::string Movie::toString()
{
    std::string s;
    s = "Title: " + title + "\n";
    s += "Genre: " + genre + "\n";
    s += "Release date: " + releaseDate + "\n";
    s += "Number of likes: " + std::to_string(numberOfLikes) + "\n";
    s += "Trailer: " + linkOfTrailer + "\n\n";
    return s;
}

void Movie::playTrailer()
{
    std::string c;
    c = "firefox ";
    c += linkOfTrailer;

    if (fork() == 0) {
        system ( c.c_str() );
        exit(0);
    }
}

void Movie::increaseNumberOfLikes()
{
    ++numberOfLikes;
}

Movie& Movie::operator=(const Movie& M)
{
    this->title = M.getTitle();
    this->genre = M.getGenre();
    this->releaseDate = M.getReleaseDate();
    this->numberOfLikes = M.getNumberOfLikes();
    this->linkOfTrailer = M.getLink();
    return *this;
}

