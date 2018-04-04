#pragma once

#include "Controller.h"
#include "Movie.h"
#include <bits/stdc++.h>

class uiAdmin {
  private:
    Controller* ctrl;


  public:
    uiAdmin(Controller& c): ctrl{&c} {}
    void setCtrl(Controller&);
	void start();
	/*
	static functions used for validation of data
	*/
	bool isleapyear(int year);
	bool valid_date(int year, int month, int day);
    bool validateNumber(std::string&);
    bool validateInput(std::string&, std::string&, std::string&,
                       std::string&, std::string&);
    void readTitleAndDate(std::string&, std::string&, int);
    void readGenrePriceLink(std::string&, std::string&, std::string&);
	//-------------------------------------------------------------------
	void printMenu();
	void displayMovies();
	void addMovie();
	void deleteMovie();
	void updateMovie();
	~uiAdmin() {
		//this->ctrl.~Controller();
	};
};
