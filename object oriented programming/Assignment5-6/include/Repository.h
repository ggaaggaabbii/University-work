#pragma once

#include <bits/stdc++.h>
#include <fstream>
#include "DynamicVector.h"
#include "Movie.h"

class Repository {
  private:
	DynamicVector<Movie> movieList;
	std::string database;

  public:
    Repository(const std::string& database = "");
	/*
	adds a movie to the repository
	input: a reference to a movie
	output: true if the element was added, false if not
	*/
	bool addMovie(const Movie&);
	/*
	deletes a movie from the repository
	input: 2 strings for the title and release date
	output: true if the element was deleted, false otherwise
	*/
    bool deleteMovie(const std::string&, const std::string&);
	/*
	updates a movie from the repository
	input: 2 strings for the title and release date, and a reference to the movie that will replace the old one
	output: true if the element was updated, false otherwise
	*/
    bool updateMovie(const std::string&, const std::string&, const Movie&);
	/*
	returns the position of a movie if it is in the repository
	input: 2 strings for the title and release date of the movie
	output: the position of the movie inside the repository or -1 if it was not found
	*/
    int findMovie(const std::string&, const std::string&);
	/*
	returns a reference to the movilist
	*/
	DynamicVector<Movie>& getList();
    void increaseNumberOfLikes(std::string&, std::string&);
	~Repository();
};
