#include "../include/UiUser.h"
#include <bits/stdc++.h>

void UiUser::setInterface()
{
    this->setWindowTitle("Watchlist");
    QHBoxLayout* h = new QHBoxLayout;
    QVBoxLayout* v = new QVBoxLayout;
    QVBoxLayout* rightSide = new QVBoxLayout;
    QHBoxLayout* watchlistButtons = new QHBoxLayout;
    searchInput = new QLineEdit;
    current = new QTableView;
    currentModel = new QStandardItemModel;
    watchlist = new QTableView;
    watchlistModel = new QStandardItemModel;
    playButton = new QPushButton{"Play"};
    nextButton = new QPushButton{"Next"};
    addButton = new QPushButton{"Add to Watchlist"};
    deleteButton = new QPushButton{"Set watched"};
    openButton = new QPushButton{"Open watchlist"};
    prevButton = new QPushButton{"Previous"};
    stats = new QPushButton{"Stats"};
    newTable = new QPushButton{"Table 2"};
    current->setModel(currentModel);
    watchlist->setModel(watchlistModel);
    current->setEditTriggers(QAbstractItemView::NoEditTriggers);
    current->setSelectionMode(QAbstractItemView::NoSelection);
    watchlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    watchlist->setSelectionMode(QAbstractItemView::SingleSelection);
    v->addWidget(searchInput);
    v->addWidget(current);
    v->addWidget(playButton);
    QHBoxLayout* nextPrev = new QHBoxLayout;
    nextPrev->addWidget(prevButton);
    nextPrev->addWidget(nextButton);
    v->addItem(nextPrev);
    v->addWidget(addButton);
    v->addWidget(stats);
    v->addWidget(newTable);
    v->setSpacing(12);
    rightSide->addWidget(watchlist);
    watchlistButtons->addWidget(deleteButton);
    watchlistButtons->addWidget(openButton);
    watchlistButtons->setSpacing(10);
    rightSide->addItem(watchlistButtons);
    rightSide->setSpacing(15);
    h->addItem(v);
    h->addItem(rightSide);
    h->setSpacing(15);
    this->setLayout(h);

}

void UiUser::setInterfacePart2()
{
    searchInput->setPlaceholderText("Search by genre");
    connect(searchInput, SIGNAL(returnPressed()), this, SLOT(filterByGenre()));
    connect(nextButton, SIGNAL(clicked(bool)), this, SLOT(next()));
    connect(playButton, SIGNAL(clicked(bool)), this, SLOT(playCurrent()));
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addToWatchlist()));
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(populateWatchlist()));
    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(openWatchlist()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteFromWatchlist()));
    connect(prevButton, SIGNAL(clicked(bool)), this, SLOT(prev()));
    connect(stats, SIGNAL(clicked(bool)), this, SLOT(showStats()));
    connect(newTable, SIGNAL(clicked(bool)), this, SLOT(showTable()));
}

void UiUser::setCurrent()
{
    currentModel->clear();

    if (toWatch.size() == 0) {
        return;
    }

    QStandardItem* item = new QStandardItem(QString::fromStdString(toWatch[ind].toString()));
    currentModel->appendRow(item);
    current->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    current->resizeRowsToContents();
    current->resizeColumnsToContents();
}

UiUser::UiUser(const std::string& typeOfStorage, const std::string& typeOfWatchlist,
               QWidget* parent) : QWidget(parent)
{
    std::shared_ptr<Repository> repo;

    if (typeOfStorage == "file") {
        std::shared_ptr<Repository> fileRepo{new FileRepo{"data.db"}};
        repo = fileRepo;

    } else {
        std::shared_ptr<Repository> fileRepo{new SQLRepo{"database.db"}};
        repo = fileRepo;
    }

    std::shared_ptr<WatchList> watchList {new WatchList};
    ctrl = new Controller{repo, watchList};

    if (typeOfWatchlist == "csv") {
        ctrl->setWatchList(std::shared_ptr <WatchList> {new CSVWatchlist{"watchlist.txt"}});

    } else {
        ctrl->setWatchList(std::shared_ptr<WatchList> {new HTMLWatchlist{"watchList.html"}});
    }

    setInterface();
    setInterfacePart2();
}

UiUser::~UiUser()
{
    delete ctrl;
}

void UiUser::filterByGenre()
{
    toWatch = ctrl->getByGenre(searchInput->text().toStdString());
    searchInput->clear();
    ind = 0;
    setCurrent();
}

void UiUser::next()
{
    ++ind;

    if ((unsigned)ind == toWatch.size()) {
        ind = 0;
    }

    setCurrent();
}

void UiUser::playCurrent()
{
    if (toWatch.size() == 0) {
        return;
    }

    toWatch[ind].playTrailer();
}

void UiUser::addToWatchlist()
{
    try {
        if (toWatch.size() == 0) {
            return;
        }

        ctrl->addToWatchList(toWatch[ind]);

    } catch (...) {

    }
}

void UiUser::populateWatchlist()
{
    watchlistModel->clear();

    for (auto it : ctrl->getWatchList()) {
        QStandardItem* item = new QStandardItem(QString::fromStdString(it.toString()));
        watchlistModel->appendRow(item);
    }

    watchlist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    watchlist->resizeColumnsToContents();
    watchlist->resizeRowsToContents();
}

void UiUser::openWatchlist()
{
    ctrl->writeWatchlist();
}

void UiUser::deleteFromWatchlist()
{
    if (watchlist->selectionModel()->selectedIndexes().count() == 0) {
        return;
    }

    QVariant a = watchlist->selectionModel()->selectedIndexes().at(0).row();
    int elem = a.toInt();

    try {
        std::vector<Movie> wList = ctrl->getWatchList();
        ctrl->removeFromWatchList(wList[elem].getTitle(), wList[elem].getReleaseDate());
        populateWatchlist();
        QMessageBox::StandardButton l;
        l = QMessageBox::question(this, "Like dialog", "Did you like the movie?", QMessageBox::Yes |
                                  QMessageBox::No);

        if (l == QMessageBox::Yes) {
            ctrl->increaseNumberOfLikes(wList[elem].getTitle(), wList[elem].getReleaseDate());
        }


    } catch (...) {

    }
}

void UiUser::prev()
{
    ind--;

    if (ind == -1) {
        ind = toWatch.size() - 1;

    }

    setCurrent();
}

void UiUser::showStats()
{
    QDialog* diag = new QDialog;
    QVBoxLayout* lay = new QVBoxLayout;
    QGraphicsView* g = new QGraphicsView;
    QGraphicsScene* scene = new QGraphicsScene;
    lay->addWidget(new QLabel{"Genres in the Watchlist:"});
    lay->addWidget(g);
    diag->setLayout(lay);
    diag->setWindowTitle("Watchlist");

    std::unordered_map<std::string, int> genres;
    int maximum = 0;

    for (auto it : ctrl->getWatchList()) {
        if (genres.find(it.getGenre()) == genres.end()) {
            genres[it.getGenre()] = 1;

        } else {
            ++genres[it.getGenre()];
            maximum = std::max(maximum, genres[it.getGenre()]);
        }
    }

    int elems = genres.size() / 2;
    int startWidth = elems * 150 - 25;
    int startHeight = maximum * 50;

    for (auto it : genres) {
        QGraphicsTextItem* text = scene->addText(QString::fromStdString(it.first + " (" + std::to_string(
                                                                            it.second) + ")"));
        text->setPos(startWidth + 25, startHeight - maximum * 50);
        QBrush redBrush(QColor{rand() % 256, rand() % 256, rand() % 256});
        QPen blackPen(Qt::black);
        QGraphicsRectItem* rect = scene->addRect(0, 0 ,
                                                 50, it.second * 50, blackPen, redBrush);
        rect->setPos(startWidth + 30, 75 + startHeight - it.second * 50);
        startWidth += 150;
    }

    g->setScene(scene);
    diag ->show();
}

void UiUser::showTable()
{
    QDialog* diag = new QDialog;
    diag->setWindowTitle("Table");
    QVBoxLayout* v = new QVBoxLayout{};
    QTableView* tab = new QTableView{};
    tab->setModel(new CostomModel{ctrl->getWlist()});
    v->addWidget(tab);
    tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tab->horizontalHeader()->resizeContentsPrecision();
    tab->resizeRowsToContents();
    tab->resizeColumnsToContents();
    diag->setLayout(v);
    diag->show();
}
