#include "../include/Repository.h"
#include <fstream>

Repository::Repository()
{
}
/*
Repository::~Repository()
{

}
*/
/*
virtual bool Repository::addMovie(const Movie& M)
{
    if (Repository::findMovie(M.getTitle(), M.getReleaseDate()) == -1) {
        movieList.push_back(M);
        return true;
    }

    CustomException e {"Could not add the movie\n"};
    throw e;
}

virtual bool Repository::deleteMovie(const std::string& title, const std::string& releaseDate)
{
    int pos = findMovie(title, releaseDate);

    if (pos == -1) {
        CustomException e{"Could not delete the movie\n"};
        throw e;
    }

    movieList[pos] = movieList[movieList.size() - 1];
    movieList.pop_back();
    return true;
}

virtual bool Repository::updateMovie(const std::string& title, const std::string& releaseDate,
                                     const Movie& M)
{
    int pos = findMovie(title, releaseDate);

    if (pos == -1) {
        CustomException e{"Could not update the movie\n"};
        throw e;
    }

    movieList[pos] = M;
    return true;
}
*/
int Repository::findMovie(const std::string& title, const std::string& releaseDate)
{
    auto rez = std::find_if(movieList.begin(), movieList.end(), [title, releaseDate](const Movie m) {
        return (m.getTitle() == title && m.getReleaseDate() == releaseDate);
    });

    if (rez != movieList.end()) {
        return rez - movieList.begin();
    }

    return -1;
}

std::vector<Movie>& Repository::getList()
{
    return movieList;
}

void Repository::increaseNumberOfLikes(const std::string& title, const std::string& releaseDate)
{
    int pos = findMovie(title, releaseDate);
    movieList[pos].increaseNumberOfLikes();
}
