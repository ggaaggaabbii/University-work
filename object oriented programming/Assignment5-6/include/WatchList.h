#ifndef WATCHLIST_H
#define WATCHLIST_H
#include "DynamicVector.h"
#include "Movie.h"

class WatchList {
  private:
    DynamicVector<Movie> toWatch;

  public:
    WatchList();
    bool addToWatchList(Movie);
    int find(std::string, std::string);
    DynamicVector<Movie>& getList();
    bool removeFromWatchList(std::string&, std::string&);
};

#endif // WATCHLIST_H
