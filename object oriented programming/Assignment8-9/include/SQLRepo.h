#ifndef SQLREPO_H
#define SQLREPO_H

#include "Repository.h"
#include <sqlite3.h>

class SQLRepo: public Repository {
    private:
        sqlite3* db;
    public:
        SQLRepo(const std::string& database = "");
        ~SQLRepo();
        bool addMovie(const Movie&);
        bool deleteMovie(const std::string&, const std::string&);
        bool updateMovie(const std::string&, const std::string&, const Movie&);
};

#endif // SQLREPO_H
