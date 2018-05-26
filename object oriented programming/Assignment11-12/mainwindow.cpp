#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    this->setWindowTitle("Watchlist");


    ui->gridLayout->setSizeConstraint(QLayout::SetFixedSize);

    ui->groupBox_3->setVisible(false);
    ui->groupBox_4->setVisible(false);
    ui->lineEdit->setEchoMode(QLineEdit::Password);

    connect(ui->Admin, SIGNAL(toggled(bool)), ui->groupBox_3, SLOT(setVisible(bool)));
    connect(ui->User, SIGNAL(toggled(bool)), ui->groupBox_4, SLOT(setVisible(bool)));
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(handleSelection()));
    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(handleSelection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleSelection()
{
    std::string file;
    std::string UI;
    std::string list;

    if (ui->database->isChecked()) {
        file = "db";

    } else if (ui->file->isChecked()) {
        file = "file";

    } else {
        return;
    }

    if (ui->Admin->isChecked()) {
        if (ui->lineEdit->text() != "parola") {
            return;
        }

        UI = "admin";

    } else if (ui->User->isChecked()) {
        if (ui->CSV->isChecked()) {
            list = "csv";

        } else if (ui->HTML->isChecked()) {
            list = "html";

        } else {
            return;
        }

    } else {
        return;
    }

    this->hide();

    if (UI == "admin") {
        UiAdmin* u = new UiAdmin{file};
        u->show();
        connect(u, SIGNAL(destroyed(QObject*)), this, SLOT(close()));

    } else {
        UiUser* u = new UiUser{file, list};
        u->show();
        connect(u, SIGNAL(destroyed(QObject*)), this, SLOT(close()));
    }
}
