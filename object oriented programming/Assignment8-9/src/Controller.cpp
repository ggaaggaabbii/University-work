#include "../include/Controller.h"

bool Controller::addMovie( Movie& M )
{
    return repo->addMovie( M );
}

bool Controller::deleteMovie( const std::string& title, const std::string& releaseDate )
{
    return repo->deleteMovie( title, releaseDate );
}

bool Controller::updateMovie( const std::string& title, const std::string& releaseDate, Movie& M )
{
    return repo->updateMovie( title, releaseDate, M );
}

std::vector<Movie>& Controller::getMovies()
{
    return repo->getList();
}

std::vector<Movie> Controller::getByGenre( const std::string genre )
{
    std::vector<Movie> v;

    for ( auto it : this->repo->getList() ) {
        if ( genre == "" || it.getGenre() == genre ) {
            v.push_back( it );
        }
    }

    return v;
}

bool Controller::addToWatchList( Movie M )
{
    return toWatch->addToWatchList( M );
}

std::vector<Movie>& Controller::getWatchList()
{
    return toWatch->getList();
}

bool Controller::removeFromWatchList( const std::string& title, const std::string& releaseDate )
{
    return toWatch->removeFromWatchList( title, releaseDate );
}

void Controller::increaseNumberOfLikes( const std::string& title, const std::string& releaseDate )
{
    repo->increaseNumberOfLikes( title, releaseDate );
}

void Controller::writeWatchlist()
{
    toWatch->openFile();
}

void Controller::setWatchList( const std::shared_ptr<WatchList>& w )
{
    toWatch = w;
}

Controller::~Controller()
{
    //std::cout << "da";
    //this->repo.~Repository();
}
