#ifndef WATCHLIST_H
#define WATCHLIST_H
#include "Movie.h"

class WatchList {
    protected:
        std::vector<Movie> toWatch;

    public:
        WatchList();
        bool addToWatchList( Movie );
        int find( const std::string&, const std::string& );
        std::vector<Movie>& getList();
        bool removeFromWatchList( const std::string&, const std::string& );
        virtual void writeToFile() {}
        virtual void openFile() {}
};

#endif // WATCHLIST_H
