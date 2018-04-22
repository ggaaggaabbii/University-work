#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "repository.h"
#include "song.h"

class Controller {
  private:
    Repository* repo;
  public:
    Controller(Repository* r);
    void add(Song& s);
    std::vector<Song> getP(int dur);
    std::vector<Song> getH(int dur);
    std::vector<Song> getAll();
};

#endif // CONTROLLER_H
