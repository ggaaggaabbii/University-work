#ifndef UIADMIN_H
#define UIADMIN_H

#include <QObject>
#include <QWidget>
#include "Controller.h"
#include "Validator.h"
#include "Repository.h"
#include "FileRepo.h"
#include "SQLRepo.h"
#include "WatchList.h"
#include "HTMLWatchlist.h"
#include "CSVWatchlist.h"
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

class UiAdmin : public QWidget {
        Q_OBJECT

    private:
        Controller* ctrl;
        Validator* valid;
        QGridLayout* g;
        QVBoxLayout* v;
        QVBoxLayout* v2;
        QHBoxLayout* h;
        QTableView* table;
        QStandardItemModel* tableModel;
        QLineEdit* titleInput;
        QLineEdit* genreInput;
        QLineEdit* dateInput;
        QLineEdit* likesInput;
        QLineEdit* linkInput;
        QPushButton* addButton;
        QPushButton* deleteButton;
        QPushButton* updateButton;

    public:
        explicit UiAdmin(const std::string&, QWidget* parent = nullptr);
        ~UiAdmin();
        void setupStuff();
        void addStuffToInterface();

    signals:

    public slots:
        void populateTable();
        void addMovie();
        void deleteMovie();
        void updateMovie();
};

#endif // UIADMIN_H
