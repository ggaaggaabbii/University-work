#include "../include/HTMLWatchlist.h"

HTMLWatchlist::HTMLWatchlist( const std::string& filename ): file{filename}
{

}

void HTMLWatchlist::writeToFile()
{
    std::ofstream g(file);
    g << "<!DOCTYPE html>\n";
    g << "<head>\n";
    g << "\t<title>Watchlist</title>\n";
    g << "</head>\n";
    g << "<body>\n";
    g << "\t<table border=\"1\">";
    g << "\t<tr>\n";
    g << "\t\t<td>Title</td>\n";
    g << "\t\t<td>Genre</td>\n";
    g << "\t\t<td>Release Date</td>\n";
    g << "\t\t<td>Number of likes</td>\n";
    g << "\t\t<td>Trailer link</td>\n";
    g << "\t</tr>\n";

    for (auto it : toWatch) {
        g << "\t<tr>\n";
        g << "\t\t<td>" << it.getTitle() << "</td>\n";
        g << "\t\t<td>" << it.getGenre() << "</td>\n";
        g << "\t\t<td>" << it.getReleaseDate() << "</td>\n";
        g << "\t\t<td>" << it.getNumberOfLikes() << "</td>\n";
        g << "\t\t<td><a href=\"" << it.getLink() << "\"</a>Link</td>\n";
        g << "\t</tr>\n";
    }

    g << "\t</table>\n";
    g << "</body>\n";

}

void HTMLWatchlist::openFile()
{
    std::string s = "firefox " + file;

    if (fork() == 0) {
        system ( s.c_str() );
        exit(0);
    }

}
