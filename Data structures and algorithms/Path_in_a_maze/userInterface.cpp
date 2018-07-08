#include "userInterface.h"

UserInterface::UserInterface(char *file) {
	fileName = std::string{file};
}
UserInterface::~UserInterface() {}

void printMenu() {
	std::cout << "0. Exit\n";
	std::cout << "1. Test if R can get out of the maze\n";
	std::cout << "2. Determine a path to get out of the maze (if there is one)\n";
	std::cout << "3. Determine a path with minimum length to get out of the maze\n";
}

void UserInterface::start() {
	std::string cmd;
	while (true) {
		printMenu();
		std::getline(std::cin, cmd);
		if (cmd == "0") {
			break;
		} else if (cmd == "1") {
			if (checkPath(fileName)) {
				std::cout << "There is a way out\n";
			} else {
				std::cout << "No way out\n";
			}
		} else if (cmd == "2") {
			path(fileName);
		} else if (cmd == "3") {
			lowestPath(fileName);
		}
	}
}