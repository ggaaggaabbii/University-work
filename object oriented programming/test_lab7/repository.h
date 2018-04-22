#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <bits/stdc++.h>
#include "song.h"

class Repository {
  private:
    std::vector<Song> elems;

  public:
    Repository();
    void add(Song& s);
    bool find(Song& s);
    std::vector<Song>getList();
};

#endif // REPOSITORY_H
