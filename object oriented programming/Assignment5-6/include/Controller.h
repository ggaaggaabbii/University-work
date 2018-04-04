#pragma once

#include "Repository.h"
#include "WatchList.h"

class Controller {
  private:
    Repository* repo;
    WatchList* toWatch;

  public:
    Controller(Repository& r, WatchList& w): repo{&r}, toWatch{&w} {}
	/*
	adds a movie to the repository
	input: a reference to a movie
	output: true if the element was added, false if not
	*/
    bool addMovie(Movie&);

	/*
	deletes a movie from the repository
	input: 2 strings for the title and release date
	output: true if the element was deleted, false otherwise
	*/
    bool deleteMovie(std::string&, std::string&);

	/*
	updates a movie from the repository
	input: 2 strings for the title and release date, and a reference to the movie that will replace the old one
	output: true if the element was updated, false otherwise
	*/
    bool updateMovie(std::string&, std::string&, Movie&);
	DynamicVector<Movie>& getMovies();
	//Controller& operator=(Controller &);
    std::vector<Movie> getByGenre(std::string genre);
    bool addToWatchList(Movie);
    /*
    returns a dynamic vector 
    */
    DynamicVector<Movie>& getWatchList();
    /*
    removes a movie from the watch list
    input: the title and the release date of the movie
    output: true if the movie was deleted, false othewise
    */
    bool removeFromWatchList(std::string&, std::string&);
    /*
    increases the number of liikes of a given movie
    input: the title and the release date of the movie
    */
    void increaseNumberOfLikes(std::string&, std::string&);
	~Controller();
};
