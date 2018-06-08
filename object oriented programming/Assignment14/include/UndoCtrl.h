#ifndef UNDOCTRL_H
#define UNDOCTRL_H

#include <bits/stdc++.h>
#include "Operation.h"
#include "CustomException.h"

class UndoCtrl {
    private:
        int index = -1;
        std::vector<std::shared_ptr<Operation> > undoList;

    public:
        UndoCtrl();
        void add(std::shared_ptr<Operation>);
        void redo();
        void undo();
};

#endif // UNDOCTRL_H
