#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include "repository.h"

class Controller : public QWidget {
        Q_OBJECT
    private:
        Repository repo;
    public:
        explicit Controller(const Repository& r, QWidget* parent = nullptr);

    signals:
        void updatedRepo();
    public slots:

    public:
        std::vector<Questions>getQuestions();
        std::vector<Questions>getSorted();
        void addQuestion(std::string id, std::string text, std::string ans, std::string points);
        int getScoreOfPart(std::string);
        std::string getQueFromIndex(int);
        void answer(int, std::string, std::string);
};

#endif // CONTROLLER_H
