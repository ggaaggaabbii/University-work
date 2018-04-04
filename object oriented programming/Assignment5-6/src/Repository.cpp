#include "../include/Repository.h"
#include <fstream>

Repository::Repository(const std::string& database)
{
	if (database == "") {
		this->database = "repo.db";
		return;
	}

    this->database = database;
	std::ifstream f(this->database);
	std::string s, delimiter = ";", output[5];

    while (getline(f, s)) {
		for (int i = 0; i < 5; ++i) {
			int pos = s.find(delimiter);
			output[i] = s.substr(0, pos);
			s.erase(0, pos + delimiter.length());
		}

        Movie M{output[0], output[1], output[2], stoi(output[3]), output[4]};
		(*this).addMovie(M);
	}

    f.close();
}
Repository::~Repository()
{
	//std::cout << "da";
	std::ofstream g(this->database);

    for (auto it : (*this).getList()) {
		g << it.computeString();
	}

    g.close();
}

bool Repository::addMovie(const Movie& M)
{
	if (Repository::findMovie(M.getTitle(), M.getReleaseDate()) == -1) {
		this->movieList.addElement(M);
		return true;
	}

    return false;
}

bool Repository::deleteMovie(const std::string& title, const std::string& releaseDate)
{
	int pos = Repository::findMovie(title, releaseDate);

    if (pos == -1) {
		return false;
	}

    this->movieList[pos] = this->movieList[this->movieList.getSize() - 1];
	this->movieList.popElement();
	return true;
}

bool Repository::updateMovie(const std::string& title, const std::string& releaseDate,
                             const Movie& M)
{
	int pos = Repository::findMovie(title, releaseDate);

    if (pos == -1) {
		return false;
	}

    this->movieList[pos] = M;
	return true;
}

int Repository::findMovie(const std::string& title, const std::string& releaseDate)
{
	int ind = 0;

    for (auto it : this->movieList) {
		if (it.getTitle() == title && it.getReleaseDate() == releaseDate)
        { return ind; }

		++ind;
	}

    return -1;
}

DynamicVector<Movie>& Repository::getList()
{
    return this->movieList;
}

void Repository::increaseNumberOfLikes(std::string& title, std::string& releaseDate)
{
    int pos = findMovie(title, releaseDate);
    movieList[pos].increaseNumberOfLikes();
}
