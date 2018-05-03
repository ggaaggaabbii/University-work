#pragma once

#include "Controller.h"
#include "Movie.h"
#include "Validator.h"
#include <bits/stdc++.h>

class uiAdmin {
  private:
    Controller* ctrl;
    Validator* valid;


  public:
    uiAdmin(Controller& c, Validator& v): ctrl{&c}, valid{&v} {}
    void setCtrl(Controller&);
    void start();

    void readTitleAndDate(std::string&, std::string&, int);
    void readGenrePriceLink(std::string&, std::string&, std::string&);
	//-------------------------------------------------------------------
	void printMenu();
	void displayMovies();
	void addMovie();
	void deleteMovie();
	void updateMovie();
	~uiAdmin() {
    }
};
