#ifndef UIPRES_H
#define UIPRES_H

#include <QObject>
#include <QWidget>
#include <bits/stdc++.h>
#include "controller.h"
#include <QListWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class UiPres : public QWidget {
        Q_OBJECT
    private:
        Controller* ctrl;
        QListWidget* list;
        QVBoxLayout* lay;
        QLineEdit* id;
        QLineEdit* text;
        QLineEdit* ans;
        QLineEdit* points;
        QPushButton* add;

    public:
        explicit UiPres(Controller* c, QWidget* parent = nullptr);

    signals:

    public slots:
        void update();
        void addQuestion();
};

#endif // UIPRES_H
