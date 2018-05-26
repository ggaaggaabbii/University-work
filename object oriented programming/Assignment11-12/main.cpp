#include "mainwindow.h"
#include "include/SelectionWindow.h"
#include <QApplication>
#include <QWidget>
#include <unistd.h>
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
#include <sqlite3.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w{};
    w.show();

    return a.exec();
}
