#ifndef UIPARTICIPANT_H
#define UIPARTICIPANT_H

#include <QObject>
#include <QWidget>
#include "controller.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>

class UiParticipant : public QWidget {
        Q_OBJECT
    private:
        Controller* ctrl;
        std::string part;
        QVBoxLayout* lay;
        QListWidget* list;
        QLineEdit* ans;
        QPushButton* btn;
        QLabel* score;
        std::unordered_set<std::string> answered;
    public:
        explicit UiParticipant(Controller*, std::string par, QWidget* parent = nullptr);

    signals:

    public slots:
        void update();
        void updateScore();
        void answer();
        void updateBtn();
};

#endif // UIPARTICIPANT_H
