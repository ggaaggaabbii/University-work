#include <QApplication>
#include "repository.h"
#include "uipart.h"
#include "controller.h"
#include "uipres.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Repository repo{"questions.txt", "participants.txt"};
    Controller* ctrl = new Controller{repo};

    for (auto it : repo.getParticipants()) {
        UiPart* u = new UiPart{it.getName(), ctrl};
        u->show();
    }

    UiPres* p = new UiPres{ctrl};
    p->show();
    return a.exec();
}
