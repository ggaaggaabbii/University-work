#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QPushButton>
#include <QDebug>
#include <QLayout>
#include <QObject>
#include <bits/stdc++.h>
#include "include/Repository.h"
#include "include/uiAdmin.h"
#include "include/uiUser.h"
#include "include/Controller.h"
#include "include/Movie.h"
#include "include/WatchList.h"
#include "include/FileRepo.h"
#include "include/Validator.h"
#include "include/CSVWatchlist.h"
#include "include/HTMLWatchlist.h"
#include "include/SQLRepo.h"
#include "include/UiAdmin.h"
#include <sqlite3.h>
#include "include/UiUser.h"

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

    public slots:
        void handleSelection();
};

#endif // MAINWINDOW_H
