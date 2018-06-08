#include "../include/UiAdmin.h"

UiAdmin::UiAdmin(const std::string& typeOfFile, QWidget* parent) : QWidget(parent)
{
    std::shared_ptr<Repository> repo;

    if (typeOfFile == "file") {
        std::shared_ptr<Repository> fileRepo{new FileRepo{"data.db"}};
        repo = fileRepo;

    } else {
        std::shared_ptr<Repository> fileRepo{new SQLRepo{"database.db"}};
        repo = fileRepo;
    }

    std::shared_ptr<WatchList> watchList {new WatchList};
    ctrl = new Controller{repo, watchList};
    valid = new Validator{};

    setupStuff();

    addStuffToInterface();

    QVBoxLayout* leftLayout = new QVBoxLayout;
    leftLayout->addItem(h);
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(deleteButton);
    buttonsLayout->addWidget(updateButton);
    leftLayout->addItem(buttonsLayout);

    g->addItem(leftLayout, 0, 1);
    g->setSpacing(10);

    this->setMinimumSize(500, 300);
    this->setLayout(g);
}

UiAdmin::~UiAdmin()
{
    delete ctrl;
    delete valid;
}

void UiAdmin::populateTable()
{

    tableModel->clear();

    for (auto it : ctrl->getMovies()) {
        QStandardItem* item = new QStandardItem{QString::fromStdString(it.toString())};

        tableModel->appendRow(item);
    }

    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    table->resizeColumnsToContents();
    table->resizeRowsToContents();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
}

void UiAdmin::deleteMovie()
{
    if (table->selectionModel()->selectedIndexes().count() == 0) {
        return;
    }

    QVariant a = table->selectionModel()->selectedIndexes().at(0).row();
    int elem = a.toInt();

    try {
        std::vector<Movie> tmp = ctrl->getMovies();
        ctrl->deleteMovie(tmp[elem].getTitle(), tmp[elem].getReleaseDate());

    } catch (...) {

    }
}

void UiAdmin::updateMovie()
{
    if (table->selectionModel()->selectedIndexes().count() == 0) {
        return;
    }

    std::string title = titleInput->text().toStdString();
    std::string genre = genreInput->text().toStdString();
    std::string releaseDate = dateInput->text().toStdString();
    std::string like = likesInput->text().toStdString();
    std::string link = linkInput->text().toStdString();

    QVariant a = table->selectionModel()->selectedIndexes().at(0).row();
    int elem = a.toInt();

    if (valid->validateInput(title, genre, releaseDate, like, link)) {
        Movie M{title, genre, releaseDate, std::stoi(like), link};

        try {
            std::vector<Movie> tmp = ctrl->getMovies();
            ctrl->updateMovie(tmp[elem].getTitle(), tmp[elem].getReleaseDate(), M);

        } catch (...) {

        }
    }
}

void UiAdmin::undo()
{
    try {
        ctrl->undo();
        populateTable();

    } catch (CustomException&) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Already the earliest version");
        messageBox.setFixedSize(500, 200);
    }
}

void UiAdmin::redo()
{
    try {
        ctrl->redo();
        populateTable();

    } catch (CustomException&) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Already the newest version");
        messageBox.setFixedSize(500, 200);
    }
}

void UiAdmin::addMovie()
{
    std::string title = titleInput->text().toStdString();
    std::string genre = genreInput->text().toStdString();
    std::string releaseDate = dateInput->text().toStdString();
    std::string like = likesInput->text().toStdString();
    std::string link = linkInput->text().toStdString();

    if (valid->validateInput(title, genre, releaseDate, like, link)) {
        Movie M{title, genre, releaseDate, std::stoi(like), link};

        try {
            ctrl->addMovie(M);

        } catch (...) {

        }
    }

    titleInput->clear();
    genreInput->clear();
    dateInput->clear();
    likesInput->clear();
    linkInput->clear();
}

void UiAdmin::setupStuff()
{
    g = new QGridLayout;
    v = new QVBoxLayout;
    v2 = new QVBoxLayout;
    h = new QHBoxLayout;
    h->setSpacing(10);
    table = new QTableView;
    titleInput = new QLineEdit;
    genreInput = new QLineEdit;
    dateInput = new QLineEdit;
    likesInput = new QLineEdit;
    linkInput = new QLineEdit;
    addButton = new QPushButton{"Add"};
    deleteButton = new QPushButton{"Delete"};
    updateButton = new QPushButton{"Update"};
    tableModel = new QStandardItemModel;
}

void UiAdmin::addStuffToInterface()
{
    g->addWidget(table);
    v->addWidget(new QLabel{"Title:"});
    v2->addWidget(titleInput);
    v->addWidget(new QLabel{"Genre:"});
    v2->addWidget(genreInput);
    v->addWidget(new QLabel{"Release Date:"});
    v2->addWidget(dateInput);
    v->addWidget(new QLabel{"Number of likes:"});
    v2->addWidget(likesInput);
    v->addWidget(new QLabel{"Trailer link:"});
    v2->addWidget(linkInput);
    h->addItem(v);
    h->addItem(v2);
    table->setModel(tableModel);
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addMovie()));
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(populateTable()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(deleteMovie()));
    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(populateTable()));
    connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(updateMovie()));
    connect(updateButton, SIGNAL(clicked(bool)), this, SLOT(populateTable()));
    und = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, SLOT(undo()));
    red = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, SLOT(redo()));
    populateTable();
}
