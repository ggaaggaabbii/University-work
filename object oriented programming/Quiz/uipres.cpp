#include "uipres.h"

UiPres::UiPres(Controller* c, QWidget* parent) : ctrl{c}, QWidget(parent)
{
    this->setWindowTitle("Presenter");
    lay = new QVBoxLayout{};
    list = new QListWidget{};
    lay->addWidget(list);
    list->setSelectionMode(QAbstractItemView::SingleSelection);
    id = new QLineEdit;
    id->setPlaceholderText("id");
    lay->addWidget(id);
    text = new QLineEdit;
    text->setPlaceholderText("question");
    lay->addWidget(text);
    ans = new QLineEdit;
    ans->setPlaceholderText("answer");
    lay->addWidget(ans);
    points = new QLineEdit;
    points->setPlaceholderText("points");
    lay->addWidget(points);
    add = new QPushButton{"Add question"};
    lay->addWidget(add);
    connect(add, SIGNAL(clicked(bool)), this, SLOT(addQuestion()));
    this->setLayout(lay);
    connect(ctrl, SIGNAL(updatedRepo()), this, SLOT(update()));
    update();
}

void UiPres::update()
{
    list->clear();

    for (auto it : ctrl->getQuestions()) {
        list->addItem(QString::fromStdString(it.getStr()));
    }
}

void UiPres::addQuestion()
{
    try {
        ctrl->addQuestion(id->text().toStdString(), text->text().toStdString(),
                          ans->text().toStdString(), points->text().toStdString());

    } catch (std::runtime_error&) {
        QMessageBox* m = new QMessageBox{};
        m->setText("unable to add the question");
        m->show();
    }
}
