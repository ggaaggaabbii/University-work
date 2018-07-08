#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <bits/stdc++.h>
#include <time.h>
#include <QMessageBox>
#include <QWidget>

class Controller: public QWidget {
        Q_OBJECT
    private:
        std::vector<std::string> words;
        std::string word;
        std::string current;
        int currentPlayer = 1;
        int score1 = 0;
        int score2 = 0;
        int currentPos;
        std::string currentLetter;

    signals:
        void scoreChanged();
        void textChanged();

    public slots:
        //void tryLetter();

    public:
        Controller();
        std::string getCurrent();
        int getScore1();
        int getScore2();
        void setCurrentPos(int);
        void setCurrentLetter(std::string);
        void check(int);
        std::string getWord();
        void setNewWord(std::string, int);
};

#endif // CONTROLLER_H
