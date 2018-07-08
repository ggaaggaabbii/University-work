#include "uiparticipant.h"

UiParticipant::UiParticipant(Controller* c, std::string par, QWidget* parent) : ctrl{c}, part{par},
    QWidget(
        parent)
{
    this->setWindowTitle(QString::fromStdString(part));
    list = new QListWidget;
    ans = new QLineEdit;
    ans->setPlaceholderText("answer");
    btn = new QPushButton{"Answer"};
    lay = new QVBoxLayout;
    score = new QLabel;
    lay->addWidget(list);
    lay->addWidget(score);
    lay->addWidget(ans);
    lay->addWidget(btn);
    this->setLayout(lay);
    update();
    updateScore();
    connect(ctrl, SIGNAL(updateList()), this, SLOT(update()));
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(answer()));
    connect(ctrl, SIGNAL(scoreUpdate()), this, SLOT(updateScore()));
    connect(list, SIGNAL(currentRowChanged(int)), this, SLOT(updateBtn()));
}

void UiParticipant::update()
{
    list->clear();

    std::vector<Question> v = ctrl->getQuestionsSorted();

    for (auto it : v) {
        list->addItem(QString::fromStdString(it.getStrParticipant()));
    }

    int i = 1;

    for (auto it : v) {
        if (answered.find(it.getStr()) != answered.end()) {
            list->setCurrentRow(i);
            list->currentItem()->setBackgroundColor(Qt::green);
        }

        ++i;
    }
}

void UiParticipant::updateScore()
{
    score->setText("Score: " + QString::fromStdString(std::to_string(ctrl->getScoreOfParticipant(
                                                                         part))));
}

void UiParticipant::answer()
{
    int l = list->currentRow();
    ctrl->answer(l, part, ans->text().toStdString());
    answered.insert(ctrl->getQuestionFromRow(l));
    list->currentItem()->setBackgroundColor(Qt::green);

    if (l == 1) {
        list->setCurrentRow(2);

    } else {
        list->setCurrentRow(1);
    }
}

void UiParticipant::updateBtn()
{
    int l = list->currentRow();

    if (l < 0) {
        return;
    }

    std::string s = ctrl->getQuestionFromRow(l);

    if (answered.find(s) != answered.end()) {
        btn->setDisabled(true);

    } else {
        btn->setDisabled(false);
    }
}
