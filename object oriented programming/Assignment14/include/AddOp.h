#ifndef ADDOP_H
#define ADDOP_H

#include "Operation.h"
#include "Repository.h"
#include <bits/stdc++.h>

class AddOp: public Operation {
    public:
        AddOp(Repository*, Movie&);
        void redo();
        void undo();
};

#endif // ADDOP_H
