#include "controller.h"

Controller::Controller()
{
    std::ifstream f("words.txt");
    std::string s;

    while (std::getline(f, s)) {
        words.push_back(s);
    }

    srand(time(NULL));
    word = words[rand() % words.size()];

    for (auto it : word) {
        current.append("_ ");
    }
}

std::string Controller::getCurrent()
{
    return current;
}

int Controller::getScore1()
{
    return score1;
}

int Controller::getScore2()
{
    return score2;
}

void Controller::setCurrentPos(int a)
{
    currentPos = a;
}

void Controller::setCurrentLetter(std::string a)
{
    currentLetter = a;
}

void Controller::check(int player)
{
    if (currentPlayer == player) {
        if (player == 2) {
            currentPlayer = 1;

        } else {
            currentPlayer = 2;
        }

        if (word[currentPos] == *(currentLetter.c_str())) {
            if (current[2 * currentPos] == word[currentPos]) {
                QMessageBox messageBox;
                messageBox.critical(0, "Error", "position already discovered");
                messageBox.setFixedSize(500, 200);
            }

            current[2 * currentPos] = word[currentPos];

            if (player == 1) {
                score1 += 1;

            } else {
                score2 += 1;
            }

            emit scoreChanged();
            emit textChanged();
        }

    } else {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Not your turn");
        messageBox.setFixedSize(500, 200);
    }
}

std::string Controller::getWord()
{
    return word;
}

void Controller::setNewWord(std::string s, int player)
{
    if (currentPlayer == player) {
        if (player == 2) {
            currentPlayer = 1;

        } else {
            currentPlayer = 2;
        }

        for (auto it : words) {
            if (it == s) {
                word = s;

                while (current.size() < 2 * word.size()) {
                    current = "_ " + current;
                }

                emit textChanged();
                break;
            }
        }

    } else {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Not your turn");
        messageBox.setFixedSize(500, 200);
    }
}


