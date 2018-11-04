#ifndef UIUSER_H
#define UIUSER_H

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
#include <QDialogButtonBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include <bits/stdc++.h>
#include <QGraphicsTextItem>
#include <QColor>

class UiUser : public QWidget {
        Q_OBJECT

    private:
        Controller* ctrl;
        QLineEdit* searchInput;
        QTableView* current;
        QStandardItemModel* currentModel;
        QTableView* watchlist;
        QStandardItemModel* watchlistModel;
        QPushButton* playButton;
        QPushButton* nextButton;
        QPushButton* prevButton;
        QPushButton* addButton;
        QPushButton* deleteButton;
        QPushButton* openButton;
        QPushButton* stats;
        std::vector<Movie> toWatch;
        int ind;
        void setInterface();
        void setInterfacePart2();
        void setCurrent();

    public:
        explicit UiUser(const std::string&, const std::string&, QWidget* parent = nullptr);
        ~UiUser();

    signals:

    public slots:
        void filterByGenre();
        void next();
        void playCurrent();
        void addToWatchlist();
        void populateWatchlist();
        void openWatchlist();
        void deleteFromWatchlist();
        void prev();
        void showStats();
};

#endif // UIUSER_H
