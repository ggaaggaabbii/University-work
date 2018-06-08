#ifndef HTMLWATCHLIST_H
#define HTMLWATCHLIST_H

#include "WatchList.h"

class HTMLWatchlist: public WatchList {
    private:
        std::string file;
    public:
        HTMLWatchlist( const std::string& );
        void writeToFile() override;
        void openFile() override;
};

#endif // HTMLWATCHLIST_H
