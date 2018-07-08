#include "uipresenter.h"

UiPresenter::UiPresenter(Controller* c, QWidget* parent) : ctrl{c}, QWidget(parent)
{
    this->setWindowTitle("Presenter");
    list = new QListWidget;
    id = new QLineEdit;
    id->setPlaceholderText("id");
    text = new QLineEdit;
    text->setPlaceholderText("text");
    ans = new QLineEdit;
    ans->setPlaceholderText("answer");
    score = new QLineEdit;
    score->setPlaceholderText("score");
    btn = new QPushButton{"Add question"};
    lay = new QVBoxLayout;
    lay->addWidget(list);
    lay->addWidget(id);
    lay->addWidget(text);
    lay->addWidget(ans);
    lay->addWidget(score);
    lay->addWidget(btn);
    this->setLayout(lay);
    update();
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(addQuestion()));
    connect(ctrl, SIGNAL(updateList()), this, SLOT(update()));
}

void UiPresenter::update()
{
    list->clear();

    std::vector<Question>v = ctrl->getQuestions();

    for (auto it : v) {
        list->addItem(QString::fromStdString(it.getStr()));
    }
}

void UiPresenter::addQuestion()
{
    try {
        ctrl->addQuestion(id->text().toStdString(), text->text().toStdString(), ans->text().toStdString(),
                          score->text().toStdString());

    } catch (...) {
        QMessageBox* m = new QMessageBox;
        m->setText("Could not add the question");
        m->show();
    }
}
