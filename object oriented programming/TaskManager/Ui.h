#ifndef UI_H
#define UI_H

#include <QObject>
#include <QWidget>
#include <bits/stdc++.h>
#include "repository.h"
#include "controller.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>

class Ui: public QWidget {
        Q_OBJECT
    private:
        std::string prog_name;
        int idProg;
        Controller* ctrl;
        QListWidget* list;
        QVBoxLayout* lay;
        QLineEdit* newTask;
        QPushButton* add;
        QPushButton* del;
        QPushButton* work;
        QPushButton* done;

    public:
        Ui();
        Ui(const std::string& p, Controller* c, int id): prog_name{p}, ctrl{c}, idProg{id} {
            this->setWindowTitle(QString::fromStdString(p));
            list = new QListWidget;
            lay = new QVBoxLayout;
            lay->addWidget(list);
            newTask = new QLineEdit;
            newTask->setPlaceholderText("new task");
            lay->addWidget(newTask);
            add = new QPushButton{"Add task"};
            lay->addWidget(add);
            del = new QPushButton{"Remove task"};
            lay->addWidget(del);
            work = new QPushButton{"Work"};
            lay->addWidget(work);
            done = new QPushButton{"Done"};
            lay->addWidget(done);
            connect(add, SIGNAL(clicked(bool)), this, SLOT(addTask()));
            connect(ctrl, SIGNAL(sendUpdate()), this, SLOT(updateList()));
            connect(del, SIGNAL(clicked(bool)), this, SLOT(remTask()));
            connect(work, SIGNAL(clicked(bool)), this, SLOT(workOnTask()));
            connect(done, SIGNAL(clicked(bool)), this, SLOT(workOnTask2()));
            connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(updateButtons()));
            //connect(add, SIGNAL(clicked(bool)), this, SLOT(close()));
            list->setSelectionMode(QAbstractItemView::SingleSelection);
            work->setDisabled(true);
            done->setDisabled(true);
            this->setLayout(lay);
            updateList();
        }

    public slots:
        void updateList();
        void addTask();
        void remTask();
        void workOnTask();
        void workOnTask2();
        void updateButtons();
};

#endif // UI_H
