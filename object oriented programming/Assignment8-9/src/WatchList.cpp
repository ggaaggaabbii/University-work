#include "../include/WatchList.h"

WatchList::WatchList()
{
}

bool WatchList::addToWatchList( Movie M )
{
    if ( find( M.getTitle(), M.getReleaseDate() ) == -1 ) {
        toWatch.push_back( M );
        writeToFile();
        return true;

    }

    CustomException e{"Could not add the movie to the watch list\n"};
    throw e;
}

int WatchList::find( const std::string& title, const std::string& releaseDate )
{
    auto rez = std::find_if( toWatch.begin(), toWatch.end(), [title, releaseDate]( const Movie m ) {
        return ( m.getTitle() == title && m.getReleaseDate() == releaseDate );
    } );

    if ( rez != toWatch.end() ) {
        return rez - toWatch.begin();
    }

    return -1;
}

std::vector<Movie>& WatchList::getList()
{
    return toWatch;
}

bool WatchList::removeFromWatchList( const std::string& title, const std::string& releaseDate )
{
    int pos = find( title, releaseDate );

    if ( pos == -1 ) {
        CustomException e{"Could not remove the movie from the watch list\n"};
        throw e;
    }

    toWatch[pos] = toWatch[toWatch.size() - 1];
    toWatch.pop_back();
    writeToFile();
    return true;
}
