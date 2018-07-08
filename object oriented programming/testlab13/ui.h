#ifndef UI_H
#define UI_H

#include <QObject>
#include <QWidget>
#include "controller.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QtCore>
#include <QObject>
#include <QLayout>
#include <QTableView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStandardItemModel>
#include <QString>
#include <QtGui>
#include <QHeaderView>
#include <QModelIndexList>
#include <QDebug>
#include <QShortcut>

class UI: public QWidget {
        Q_OBJECT

    private:
        Controller* ctrl;
        QLabel* w;
        std::string word;
        QLineEdit* index;
        QLineEdit* letter;
        QLineEdit* prefix;
        QPushButton* tryBtn;
        QPushButton* change;
        int id;

    public:
        UI();
        UI(Controller*, int);
        ~UI();

    public slots:
        void sendGuess();
        void sendPre();
        void update();
};

#endif // UI_H
