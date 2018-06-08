#include "../include/FileRepo.h"

FileRepo::FileRepo(const std::string& database)
{
    if (database == "") {
        this->database = "repo.db";
        return;
    }

    this->database = database;
    std::ifstream f(database);
    Movie M{};

    while (f >> M) {
        addMovie(M);
    }

    f.close();
}

FileRepo::~FileRepo()
{
    std::ofstream g(database);
    std::for_each(movieList.begin(), movieList.end(), [&g](const Movie & m) {g << m;});
    g.close();
}
