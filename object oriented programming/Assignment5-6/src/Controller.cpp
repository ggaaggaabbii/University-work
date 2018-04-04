#include "../include/Controller.h"

bool Controller::addMovie(Movie& M)
{
	return (*(this->repo)).addMovie(M);
}

bool Controller::deleteMovie(std::string& title, std::string& releaseDate)
{
	return (*(this->repo)).deleteMovie(title, releaseDate);
}

bool Controller::updateMovie(std::string& title, std::string& releaseDate, Movie& M)
{
	return (*(this->repo)).updateMovie(title, releaseDate, M);
}
/*
Controller& Controller::operator=(Controller &C) {
    this->repo = C.getRepo();
}
*/

DynamicVector<Movie>& Controller::getMovies()
{
    return (*(this->repo)).getList();
}

std::vector<Movie> Controller::getByGenre(std::string genre)
{
    std::vector<Movie> v;

    for (auto it : this->repo->getList()) {
        if (genre == "" || it.getGenre() == genre) {
            v.push_back(it);
        }
    }

    return v;
}

bool Controller::addToWatchList(Movie M)
{
    return toWatch->addToWatchList(M);
}

DynamicVector<Movie>& Controller::getWatchList()
{
    return (*(this->toWatch)).getList();
}

bool Controller::removeFromWatchList(std::string& title, std::string& releaseDate)
{
    return toWatch->removeFromWatchList(title, releaseDate);
}

void Controller::increaseNumberOfLikes(std::string& title, std::string& releaseDate)
{
    repo->increaseNumberOfLikes(title, releaseDate);
}

Controller::~Controller()
{
	//std::cout << "da";
	//this->repo.~Repository();
}
