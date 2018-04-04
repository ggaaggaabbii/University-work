#include "../include/uiUser.h"

void uiUser::start()
{
    std::string command;

    while (true) {
        printMenu();
        std::getline(std::cin, command);

        if (command == "0") {
            std::cout << "Exiting...\n";
            break;
        } else if (command == "1") {
            printMovies();
        } else if (command == "2") {
            printWatchList();
        } else if (command == "3") {
            removeFromWatchList();
        } else {
            std::cout << "Invalid command\n";
        }
    }
}

void uiUser::printMovies()
{
    std::string genre;
    std::cout << "Give the genre:\n";
    std::getline(std::cin, genre);
    std::cout << "\n";
    std::vector<Movie> v = ctrl->getByGenre(genre);

    if (v.size() == 0) {
        std::cout << "No such movie was found\n";
        return;
    }

    int ind = 0;
    std::string commad;
    bool ok = true;

    while (true) {
        if (ok) {std::cout << v[ind].toString(); v[ind].playTrailer(); }

        printSubmenu();
        std::getline(std::cin, commad);

        if (commad == "0") {
            return;
        } else if (commad == "1") {
            ind++;
            ok = true;

            if ((unsigned)ind == v.size()) {
                ind = 0;
            }
        } else if (commad == "2") {
            if (ctrl->addToWatchList(v[ind]) == false) {
                std::cout << "Movie already in watch list\n";
            }

            ok = false;
        } else {
            std::cout << "Invalid command\n";
            ok = false;
        }
    }
}

void uiUser::printMenu()
{
    std::cout << "0. Exit\n";
    std::cout << "1. Display movies for a given genre\n";
    std::cout << "2. Display watchlist\n";
    std::cout << "3. Remove from watchlist\n";
}

void uiUser::printSubmenu()
{
    std::cout << "0. Back\n";
    std::cout << "1. Next\n";
    std::cout << "2. Add to watch list\n";
}

void uiUser::printWatchList()
{
    DynamicVector<Movie> v = ctrl->getWatchList();

    if (v.getSize() == 0) {
        std::cout << "No movie in the watch list\n";
    }

    for (auto it : v) {
        std::cout << it.toString();
    }
}

void uiUser::removeFromWatchList()
{
    std::string title, releaseDate;
    std::cout << "Give the title:\n";
    std::getline(std::cin, title);
    std::cout << "Give the release date:\n";
    std::getline(std::cin, releaseDate);

    if (ctrl->removeFromWatchList(title, releaseDate) == false) {
        std::cout << "No such movie in the watch list\n";
        return;
    }

    std::cout << "Did you like the movie? [y/n]\n";
    std::string reaction;
    std::getline(std::cin, reaction);

    while (reaction != "y" && reaction != "n") {
        std::getline(std::cin, reaction);
    }

    if (reaction == "y") {
        ctrl->increaseNumberOfLikes(title, releaseDate);
    }
}
