#ifndef DELOP_H
#define DELOP_H

#include "Repository.h"
#include <bits/stdc++.h>
#include "Movie.h"
#include "Operation.h"

class DelOp: public Operation {

    public:
        DelOp(Repository*, Movie&);
        void redo();
        void undo();
};

#endif // DELOP_H
