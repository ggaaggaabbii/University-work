#include "../include/uiAdmin.h"

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
    readTitleAndDate(title, releaseDate, 0);
    readGenrePriceLink(genre, likes, link);

    if (valid->validateInput(title, genre, releaseDate, likes, link)) {
		Movie M{title, genre, releaseDate, stoi(likes), link};
        ctrl->addMovie(M);
        std::cout << "Succesfully added the movie\n";
		return;
	}

    CustomException e{"At least one field is invalid!\n"};
    throw e;
}

void uiAdmin::deleteMovie()
{
	std::string title, releaseDate;
    readTitleAndDate(title, releaseDate, 0);
    ctrl->deleteMovie(title, releaseDate);
    std::cout << "Succesfully deleted the movie\n";
}

void uiAdmin::updateMovie()
{
	std::string title, genre, releaseDate, likes, link;
	std::string title2, releaseDate2;
    readTitleAndDate(title2, releaseDate2, 1);
    readTitleAndDate(title, releaseDate, 2);
    readGenrePriceLink(genre, likes, link);

    if (valid->validateInput(title, genre, releaseDate, likes, link)) {
		Movie M{title, genre, releaseDate, stoi(likes), link};
        ctrl->updateMovie(title2, releaseDate2, M);
        std::cout << "Succesfully updated the movie\n";
		return;
	}

    CustomException e{"At least one field is invalid!\n"};
    throw e;
}

void uiAdmin::displayMovies()
{
    for (auto it : ctrl->getMovies()) {
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
        try {
            printMenu();
            std::getline(std::cin, command);

            if (command == "0") {
                std::cout << "Exiting...";
                break;
            } else if (command == "2") {
                addMovie();
            } else if (command == "1") {
                displayMovies();
            } else if (command == "3") {
                deleteMovie();
            } else if (command == "4") {
                updateMovie();
            } else {
                std::cout << "Invalid input!\n";
            }
        } catch (std::exception& e) {
            std::cout << e.what();
        }
	}
}
