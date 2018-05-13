#pragma once

#include "Repository.h"
#include "WatchList.h"
#include <bits/stdc++.h>

class Controller {
    private:
        std::shared_ptr<Repository> repo;
        std::shared_ptr<WatchList> toWatch;

    public:

        Controller ( std::shared_ptr<Repository> r, std::shared_ptr<WatchList> w ) : repo{r}, toWatch{w}  {}
        /*
        adds a movie to the repository
        input: a reference to a movie
        output: true if the element was added, false if not
        */
        bool addMovie ( Movie& );

        /*
        deletes a movie from the repository
        input: 2 strings for the title and release date
        output: true if the element was deleted, false otherwise
        */
        bool deleteMovie ( const std::string&, const std::string& );

        /*
        updates a movie from the repository
        input: 2 strings for the title and release date, and a reference to the movie that will replace the old one
        output: true if the element was updated, false otherwise
        */
        bool updateMovie ( const std::string&, const std::string&, Movie& );
        std::vector<Movie>& getMovies();
        //Controller& operator=(Controller &);
        std::vector<Movie> getByGenre ( const std::string genre );
        bool addToWatchList ( Movie );
        /*
        returns a dynamic vector
        */
        std::vector<Movie>& getWatchList();
        /*
        removes a movie from the watch list
        input: the title and the release date of the movie
        output: true if the movie was deleted, false othewise
        */
        bool removeFromWatchList ( const std::string&, const std::string& );
        /*
        increases the number of liikes of a given movie
        input: the title and the release date of the movie
        */
        void increaseNumberOfLikes ( const std::string&, const std::string& );
        void writeWatchlist();
        void setWatchList( const std::shared_ptr<WatchList>& );
        ~Controller();
};
