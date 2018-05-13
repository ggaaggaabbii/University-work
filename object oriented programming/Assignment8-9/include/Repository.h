#pragma once

#include <bits/stdc++.h>
#include <fstream>
#include "Movie.h"

class Repository {
    protected:
        std::vector<Movie> movieList;
        std::string database;

    public:
        Repository();
        /*
        adds a movie to the repository
        input: a reference to a movie
        output: true if the element was added, false if not
        */
        virtual bool addMovie(const Movie& M) {
            if (Repository::findMovie(M.getTitle(), M.getReleaseDate()) == -1) {
                movieList.push_back(M);
                return true;
            }

            CustomException e {"Could not add the movie\n"};
            throw e;
        }
        /*
        deletes a movie from the repository
        input: 2 strings for the title and release date
        output: true if the element was deleted, false otherwise
        */
        virtual bool deleteMovie(const std::string& title, const std::string& releaseDate) {
            int pos = findMovie(title, releaseDate);

            if (pos == -1) {
                CustomException e{"Could not delete the movie\n"};
                throw e;
            }

            movieList[pos] = movieList[movieList.size() - 1];
            movieList.pop_back();
            return true;
        }
        /*
        updates a movie from the repository
        input: 2 strings for the title and release date, and a reference to the movie that will replace the old one
        output: true if the element was updated, false otherwise
        */
        virtual bool updateMovie(const std::string& title, const std::string& releaseDate,
                                 const Movie& M) {
            int pos = findMovie(title, releaseDate);

            if (pos == -1) {
                CustomException e{"Could not update the movie\n"};
                throw e;
            }

            movieList[pos] = M;
            return true;
        }
        /*
        returns the position of a movie if it is in the repository
        input: 2 strings for the title and release date of the movie
        output: the position of the movie inside the repository or -1 if it was not found
        */
        int findMovie(const std::string&, const std::string&);
        /*
        returns a reference to the movilist
        */
        std::vector<Movie>& getList();
        void increaseNumberOfLikes(const std::string&, const std::string&);
        virtual ~Repository() {}
};
