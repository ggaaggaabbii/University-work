#ifndef UPDATEOP_H
#define UPDATEOP_H

#include "Operation.h"
#include "Repository.h"
#include "Movie.h"
#include <bits/stdc++.h>

class UpdateOp : public Operation {
    private:
        Movie oldM;
    public:
        UpdateOp(Repository*, Movie&, Movie&);
        void redo();
        void undo();
};

#endif // UPDATEOP_H
