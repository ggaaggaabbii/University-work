#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "controller.h"
#include "ui.h"
#include <QLabel>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow* ui;
        Controller* ctrl;
        QLabel* l1;
        QLabel* l2;
        int score1;
        int score2;
    public slots:
        void update();
};

#endif // MAINWINDOW_H
