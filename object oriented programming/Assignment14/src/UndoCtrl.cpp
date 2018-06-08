#include "include/UndoCtrl.h"

UndoCtrl::UndoCtrl()
{

}

void UndoCtrl::add(std::shared_ptr<Operation>op)
{
    while (undoList.size() + 1 > (unsigned)index) {
        undoList.pop_back();
    }

    ++index;
    undoList.push_back(op);
}

void UndoCtrl::redo()
{
    if ((unsigned)index + 1 >= undoList.size() || undoList.size() == 0) {
        throw CustomException{"Already the newest version"};
    }

    undoList[++index]->redo();
}

void UndoCtrl::undo()
{
    if (index < 0) {
        throw CustomException{"Already the latest version"};
    }

    undoList[index--]->undo();
}
