#include "../include/Controller.h"

bool Controller::addMovie( Movie& M )
{
    bool a = repo->addMovie( M );
    undoCtrl.add(std::shared_ptr<Operation> {new AddOp{repo.get(), M}});
    return a;
}

bool Controller::deleteMovie( const std::string& title, const std::string& releaseDate )
{
    Movie M = repo->getList()[repo->findMovie(title, releaseDate)];
    bool a = repo->deleteMovie( title, releaseDate );
    undoCtrl.add(std::shared_ptr<Operation> {new DelOp{repo.get(), M}});
    return a;
}

bool Controller::updateMovie( const std::string& title, const std::string& releaseDate, Movie& M )
{
    Movie m = repo->getList()[repo->findMovie(title, releaseDate)];
    bool a = repo->updateMovie( title, releaseDate, M );
    undoCtrl.add(std::shared_ptr<Operation> {new UpdateOp{repo.get(), M, m}});
    return a;
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

void Controller::undo()
{
    undoCtrl.undo();
}

void Controller::redo()
{
    undoCtrl.redo();
}

WatchList& Controller::getWlist()
{
    return *toWatch;
}

Controller::~Controller()
{
    //std::cout << "da";
    this->repo->~Repository();
}
