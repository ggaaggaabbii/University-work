#include "include/DelOp.h"

DelOp::DelOp(Repository* r, Movie& m)
{
    repo = r;
    M = m;
}

void DelOp::redo()
{
    repo->deleteMovie(M.getTitle(), M.getReleaseDate());
}

void DelOp::undo()
{
    repo->addMovie(M);
}
