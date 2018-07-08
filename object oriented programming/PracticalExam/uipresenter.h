#ifndef UIPRESENTER_H
#define UIPRESENTER_H

#include <QObject>
#include <QWidget>
#include "controller.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QMessageBox>

class UiPresenter : public QWidget {
        Q_OBJECT
    private:
        Controller* ctrl;
        QVBoxLayout* lay;
        QListWidget* list;
        QLineEdit* id;
        QLineEdit* text;
        QLineEdit* ans;
        QLineEdit* score;
        QPushButton* btn;
    public:
        explicit UiPresenter(Controller*, QWidget* parent = nullptr);

    signals:

    public slots:
        void update();
        void addQuestion();
};

#endif // UIPRESENTER_H
