#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QWidget>
#include "repository.h"
#include <QDebug>

class Controller : public QWidget {
        Q_OBJECT
    private:
        Repository repo;
    public:
        explicit Controller(const Repository&, QWidget* parent = nullptr);
        std::vector<Question> getQuestions();
        int getScoreOfParticipant(const std::string&);
        std::vector<Question> getQuestionsSorted();
        void addQuestion(const std::string&, const std::string&, const std::string&, const std::string&);
        void answer(int, const std::string&, const std::string&);
        std::string getQuestionFromRow(int);

    signals:
        void updateList();
        void scoreUpdate();

    public slots:
};

#endif // CONTROLLER_H
