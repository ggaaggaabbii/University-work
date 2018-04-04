#include "../include/uiAdmin.h"

bool uiAdmin::isleapyear(int year)
{
	return ((!(year % 4) && (year % 100)) || !(year % 400));
}

bool uiAdmin::valid_date(int year, int month, int day)
{
	int monthlen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (!year || !month || !day || month > 12)
    { return 0; }

	if (isleapyear(year) && month == 2)
    { monthlen[1]++; }

	if (day > monthlen[month - 1])
    { return 0; }

	return 1;
}

bool uiAdmin::validateNumber(std::string& s)
{
	for (auto it : s) {
		if (it < '0' || it > '9')
        { return false; }
	}

    return true;
}

bool uiAdmin::validateInput(std::string& title, std::string& genre,
                            std::string& releaseDate, std::string& likes, std::string& link)
{
	if (title == "" || releaseDate == "" || genre == "" || link == "" || likes == "")
    { return false; }

    if (releaseDate.length() != 10) { return false; }

	int y, m, d;
	std::string year = releaseDate.substr(0, 4), day = releaseDate.substr(8, 2);
	std::string month = releaseDate.substr(5, 2);

    if (validateNumber(year) == false || validateNumber(month) == false ||
            validateNumber(day) == false) {
		return false;
	}

    std::string s;
	s = releaseDate.substr(0, 4);
	y = stoi(s);
	s = releaseDate.substr(5, 7);
	m = stoi(s);
	s = releaseDate.substr(8, 10);
	d = stoi(s);

    if (valid_date(y, m, d) == false) { return false; }

    if (releaseDate[4] != '-' || releaseDate[7] != '-') { return false; }

    if (validateNumber(likes) == false) { return false; }

	return true;
}


void uiAdmin::readTitleAndDate(std::string& title, std::string& releaseDate, int caller)
{
	std::cout << "Introduce the ";

    if (caller == 1)
    { std::cout << "old "; }
	else if (caller == 2)
    { std::cout << "new "; }

	std::cout << "title of the movie:\n";
    std::getline(std::cin, title);
	std::cout << "Introduce the ";

    if (caller == 1)
    { std::cout << "old "; }
	else if (caller == 2)
    { std::cout << "new "; }

	std::cout << "release date (yyyy-mm-dd) of the movie:\n";
    std::getline(std::cin, releaseDate);
}
void uiAdmin::readGenrePriceLink(std::string& genre, std::string& likes, std::string& link)
{
	std::cout << "Introduce the genre of the movie:\n";
    std::getline(std::cin, genre);
	std::cout << "Introduce the number of likes of the movie:\n";
    std::getline(std::cin, likes);
	std::cout << "Introduce the link of the trailer of the movie:\n";
    std::getline(std::cin, link);
}

void uiAdmin::addMovie()
{
	std::string title, genre, releaseDate, likes, link;
	(*this).readTitleAndDate(title, releaseDate, 0);
	(*this).readGenrePriceLink(genre, likes, link);

    if ((*this).validateInput(title, genre, releaseDate, likes, link)) {
		Movie M{title, genre, releaseDate, stoi(likes), link};

        if ((*(this->ctrl)).addMovie(M) == false)
        { std::cout << "Movie already in the repository!\n"; }
		else
        { std::cout << "Succesfully added the movie\n"; }

		return;
	}

    std::cout << "At least one field is invalid!\n";
}

void uiAdmin::deleteMovie()
{
	std::string title, releaseDate;
	(*this).readTitleAndDate(title, releaseDate, 0);

    if ((*(this->ctrl)).deleteMovie(title, releaseDate) == false) {
		std::cout << "Error while deleting the movie...\n";
		return;
	}

    std::cout << "Succesfully deleted the movie\n";
}

void uiAdmin::updateMovie()
{
	std::string title, genre, releaseDate, likes, link;
	std::string title2, releaseDate2;
	(*this).readTitleAndDate(title2, releaseDate2, 1);
	(*this).readTitleAndDate(title, releaseDate, 2);
	(*this).readGenrePriceLink(genre, likes, link);

    if ((*this).validateInput(title, genre, releaseDate, likes, link)) {
		Movie M{title, genre, releaseDate, stoi(likes), link};

        if ((*(this->ctrl)).updateMovie(title2, releaseDate2, M) == false)
        { std::cout << "Movie could not be updated!\n"; }
		else
        { std::cout << "Succesfully updated the movie\n"; }

		return;
	}

    std::cout << "At least one field is invalid!\n";
}

void uiAdmin::displayMovies()
{
	for (auto it : (*(this->ctrl)).getMovies()) {
        std::cout << it.toString();
	}
}

void uiAdmin::printMenu()
{
	std::cout << "Menu:\n";
	std::cout << "0. Exit\n";
	std::cout << "1. Display movies\n";
	std::cout << "2. Add movie\n";
	std::cout << "3. Delete movie\n";
	std::cout << "4. Update movie\n";
}

void uiAdmin::start()
{
	std::string command;

    while (true) {
		(*this).printMenu();
        std::getline(std::cin, command);

		if (command == "0") {
			std::cout << "Exiting...";
			break;
		} else if (command == "2") {
			(*this).addMovie();
		} else if (command == "1") {
			(*this).displayMovies();
		} else if (command == "3") {
			(*this).deleteMovie();
		} else if (command == "4") {
			(*this).updateMovie();
		} else {
			std::cout << "Invalid input!\n";
		}
	}
}
