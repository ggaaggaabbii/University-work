#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ctrl = new Controller;
    UI* p1 = new UI{ctrl, 1};
    UI* p2 = new UI{ctrl, 2};
    p1->show();
    p2->show();
    QVBoxLayout* v = new QVBoxLayout;
    l1 = new QLabel{"Player1: 0"};
    l2 = new QLabel{"Player2: 0"};
    v->addWidget(l1);
    v->addWidget(l2);
    ui->centralWidget->setLayout(v);
    connect(ctrl, SIGNAL(scoreChanged()), this, SLOT(update()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete ctrl;
}

void MainWindow::update()
{
    score1 = ctrl->getScore1();
    score2 = ctrl->getScore2();
    l1->setText("Player1: " + QString::fromStdString(std::to_string(score1)));
    l2->setText("Player2: " + QString::fromStdString(std::to_string(score2)));
}
