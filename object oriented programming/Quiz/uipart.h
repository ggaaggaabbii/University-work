#ifndef UIPART_H
#define UIPART_H

#include <QObject>
#include <QWidget>
#include <bits/stdc++.h>
#include "controller.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class UiPart : public QWidget {
        Q_OBJECT
    private:
        std::string name;
        Controller* ctrl;
        QListWidget* list;
        QVBoxLayout* lay;
        QLineEdit* ans;
        QPushButton* btn;
        QLabel* score;
        std::unordered_map<std::string, bool>answeredQ;
    public:
        explicit UiPart(const std::string& n, Controller* c, QWidget* parent = nullptr);

    signals:

    public slots:
        void update();
        void updateScore();
        void updateBtn();
};

#endif // UIPART_H
