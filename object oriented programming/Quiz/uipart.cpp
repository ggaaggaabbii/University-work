#include "uipart.h"

UiPart::UiPart(const std::string& n, Controller* c, QWidget* parent) : name{n}, ctrl{c}, QWidget(
        parent)
{
    this->setWindowTitle(QString::fromStdString(name));
    lay = new QVBoxLayout{};
    list = new QListWidget{};
    lay->addWidget(list);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    ans = new QLineEdit;
    ans->setPlaceholderText("answer");
    score = new QLabel;
    lay->addWidget(score);
    lay->addWidget(ans);
    btn = new QPushButton{"answer"};
    lay->addWidget(btn);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(updateScore()));
    this->setLayout(lay);
    update();
    score->setText("Score: " + QString::fromStdString(std::to_string(ctrl->getScoreOfPart(name))));
    connect(ctrl, SIGNAL(updatedRepo()), this, SLOT(update()));
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(updateBtn()));
}

void UiPart::update()
{
    list->clear();

    for (auto it : ctrl->getSorted()) {
        list->addItem(QString::fromStdString(it.getPartStr()));
    }

    int i = 0;

    for (auto it : ctrl->getSorted()) {
        std::string s = it.getStr();

        if (answeredQ.find(s) != answeredQ.end()) {
            list->setCurrentRow(i);
            list->currentItem()->setBackgroundColor(Qt::green);
        }

        ++i;
    }
}

void UiPart::updateScore()
{
    try {
        int l = list->currentRow();
        std::string s = ctrl->getQueFromIndex(l);
        ctrl->answer(l, name, ans->text().toStdString());
        answeredQ[s] = true;
        list->currentItem()->setBackgroundColor(Qt::green);
        list->setCurrentRow(0);

    } catch (...) {

    }

    score->setText("Score: " + QString::fromStdString(std::to_string(ctrl->getScoreOfPart(name))));
}

void UiPart::updateBtn()
{
    int l = list->currentRow();
    std::string s = ctrl->getQueFromIndex(l);

    if (answeredQ.find(s) != answeredQ.end()) {
        btn->setDisabled(true);

    } else {
        btn->setDisabled(false);
    }
}
