#include "ui.h"

UI::UI()
{

}

UI::UI(Controller* c, int pl): ctrl{c}, id{pl}
{
    word = ctrl->getCurrent();
    QVBoxLayout* v = new QVBoxLayout;
    w = new QLabel{QString::fromStdString(word)};
    index = new QLineEdit;
    letter = new QLineEdit;
    tryBtn = new QPushButton{"Try"};
    prefix = new QLineEdit;
    change = new QPushButton{"Change"};
    v->addWidget(w);
    v->addWidget(index);
    v->addWidget(letter);
    v->addWidget(tryBtn);
    v->addWidget(prefix);
    v->addWidget(change);
    connect(tryBtn, SIGNAL(clicked(bool)), this, SLOT(sendGuess()));
    connect(ctrl, SIGNAL(textChanged()), this, SLOT(update()));
    connect(change, SIGNAL(clicked(bool)), this, SLOT(sendPre()));
    this->setLayout(v);
}

UI::~UI()
{

}

void UI::sendGuess()
{
    ctrl->setCurrentPos(stoi(index->text().toStdString()));
    ctrl->setCurrentLetter(letter->text().toStdString());
    ctrl->check(id);
}

void UI::sendPre()
{
    std::string s;
    s = prefix->text().toStdString();
    s += ctrl->getWord();
    ctrl->setNewWord(s, id);
}

void UI::update()
{
    word = ctrl->getCurrent();
    w->setText(QString::fromStdString(word));

    for (auto it : word) {
        if (it == '_') {
            return;
        }
    }


    QMessageBox messageBox;
    messageBox.critical(0, "Info", "Player won");
    messageBox.setFixedSize(500, 200);
}
