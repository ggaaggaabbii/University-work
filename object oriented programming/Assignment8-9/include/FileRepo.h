#ifndef FILEREPO_H
#define FILEREPO_H

#include "Repository.h"
#include "Movie.h"

class FileRepo: public Repository {

  public:
    FileRepo(const std::string& database = "");
    ~FileRepo();
};

#endif // FILEREPO_H
