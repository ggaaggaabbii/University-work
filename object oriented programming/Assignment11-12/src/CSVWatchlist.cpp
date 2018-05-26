#include "../include/CSVWatchlist.h"

CSVWatchlist::CSVWatchlist( const std::string& fileName ): file{fileName}
{

}

void CSVWatchlist::writeToFile()
{
    std::ofstream g ( file );

    for ( auto it : toWatch ) {
        g << it;
    }

    g.close();

}

void CSVWatchlist::openFile()
{
    std::string s = "leafpad " + file;

    if (fork() == 0) {
        system ( s.c_str() );
        exit(0);
    }
}
