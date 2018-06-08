#ifndef OPERATION_H
#define OPERATION_H

#include "Repository.h"
#include "Movie.h"

class Operation {
    protected:
        Repository* repo;
        Movie M;

    public:
        Operation();
        virtual void redo() = 0;
        virtual void undo() = 0;
};

#endif // OPERATION_H
