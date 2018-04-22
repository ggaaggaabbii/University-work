#ifndef SONG_H
#define SONG_H

#include <bits/stdc++.h>

class Song {
  private:
    int id;
    std::string title;
    std::string artist;
    int duration;
    double heaviness;

  public:
    Song();
    Song(int, std::string, std::string, int, double);
    Song& operator=(Song& s);

    int getId();
    std::string getTitle();
    std::string getArtist();
    int getDur();
    double getHe();
    std::string toStr();
    bool operator<(const Song& rhs) const { return heaviness < rhs.heaviness; }
};

#endif // SONG_H
