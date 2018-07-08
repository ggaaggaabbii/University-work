#include <QApplication>
#include "repository.h"
#include "controller.h"
#include "uipresenter.h"
#include "uiparticipant.h"

void test()
{
    Repository repo{"", ""};
    Question q{1, "1", "1", 1};
    repo.addQuestion(q);
    std::vector<Question> v = repo.getQuestions();
    assert(v[0].getStr() == q.getStr());
    Participant p{"ion", 10};
    repo.addPart(p);
    repo.answer("ion", 10);
    std::vector<Participant> parts = repo.getParticipants();
    assert(parts[0].getScore() == 20);
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //test();
    Repository repo{"questions.txt", "participants.txt"};
    Controller* ctrl = new Controller{repo};
    UiPresenter* u = new UiPresenter{ctrl};
    u->show();

    for (auto it : repo.getParticipants()) {
        UiParticipant* ui = new UiParticipant{ctrl, it.getName()};
        ui->show();
    }

    return a.exec();
}
