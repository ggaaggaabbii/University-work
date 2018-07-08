#include <QApplication>
#include "repository.h"
#include "controller.h"
#include "Ui.h"

void test()
{
    Repository r{""};
    Task t{"task1", 1, 0};
    Task t1{"task2", 2, 0};

    r.addTask(t);
    r.addTask(t1);
    r.workOnTask(t, 1);
    assert(r.getTasks()[0].getStatus() == "in progress");
    assert(r.getTasks()[0].getProg() == 1);
    t.setStatus("in progress");
    r.workOnTask2(t, 1);
    assert(r.getTasks()[0].getStatus() == "closed");

    r.workOnTask(t1, 2);
    assert(r.getTasks()[1].getStatus() == "in progress");
    assert(r.getTasks()[1].getProg() == 2);
    t1.setStatus("in progress");
    r.workOnTask2(t1, 2);
    assert(r.getTasks()[1].getStatus() == "closed");
}


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    //test();
    Repository repo{"programmers.txt"};
    Controller* ctrl = new Controller{repo};

    for (auto it : repo.getProg()) {
        Ui* u = new Ui{it.getName(), ctrl, it.getId()};
        u->show();
    }

    return a.exec();
}
