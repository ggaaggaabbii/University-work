#ifndef CSVWATCHLIST_H
#define CSVWATCHLIST_H

#include "WatchList.h"
#include "Movie.h"
#include <bits/stdc++.h>

class CSVWatchlist: public WatchList {
    private:
        std::string file;
    public:
        CSVWatchlist( const std::string& );
        void writeToFile() override;
        void openFile() override;
};

#endif // CSVWATCHLIST_H
