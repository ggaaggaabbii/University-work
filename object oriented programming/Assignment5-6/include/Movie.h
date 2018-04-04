#pragma once

#include <bits/stdc++.h>

class Movie {
    //we consider movies uniquely idetified by the title and release date
  private:
	std::string title;
	std::string genre;
	std::string releaseDate;
	long long numberOfLikes;
	std::string linkOfTrailer;


  public:
    Movie(const std::string& T = "", const std::string& G = "",
          const std::string& R = "", long long likes = 0, const std::string& Link = ""):
		title{T}, genre{G}, releaseDate{R}, numberOfLikes{likes}, linkOfTrailer{Link}
	{}
	Movie(const Movie&);
	/*
	Getters
	*/
	std::string getTitle() const;
	std::string getGenre() const;
	std::string getReleaseDate() const;
	long long getNumberOfLikes() const;
	std::string getLink() const;
	/*
	Setters
	*/
    void setTitle(const std::string&);
    void setGenre(const std::string&);
    void setReleaseDate(const std::string&);
	void setNumbersOfLikes(const long long);
    void setLink(const std::string&);

    bool operator==(const Movie&);

    Movie& operator=(const Movie&);

    bool operator!=(const Movie&);
	/*
	computes the string that needs to be written in the database
	output: a string with all the data from a movie concatenated
	*/
	std::string computeString();

    std::string toString();

    void playTrailer();
    void increaseNumberOfLikes();

	~Movie();
};
