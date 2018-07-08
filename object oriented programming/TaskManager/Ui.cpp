#include "Ui.h"

Ui::Ui()
{

}

void Ui::updateList()
{
    list->clear();

    for (auto it : ctrl->getSortedTasks()) {
        QString s = QString::fromStdString(it.getStr());
        QListWidgetItem* itm = new QListWidgetItem{s};
        list->addItem(itm);
    }
}

void Ui::addTask()
{
    ctrl->addTask(newTask->text().toStdString());
}

void Ui::remTask()
{
    int l = list->currentRow();
    ctrl->remTask(l);
}

void Ui::workOnTask()
{
    int l = list->currentRow();
    ctrl->workOnTask(l, idProg);
}

void Ui::workOnTask2()
{
    int l = list->currentRow();
    ctrl->workOnTask2(l, idProg);
}

void Ui::updateButtons()
{
    int l = list->currentRow();

    if (ctrl->getTaskFromInd(l).getStatus() == "open") {
        work->setDisabled(false);
        done->setDisabled(true);

    } else if (ctrl->getTaskFromInd(l).getStatus() == "in progress" &&
               ctrl->getTaskFromInd(l).getId() == idProg) {
        work->setDisabled(true);
        done->setDisabled(false);

    } else {
        work->setDisabled(true);
        done->setDisabled(true);
    }
}
