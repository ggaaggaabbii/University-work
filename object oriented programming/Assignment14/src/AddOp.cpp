#include "include/AddOp.h"

AddOp::AddOp(Repository* r, Movie& m)
{
    repo = r;
    M = m;
}

void AddOp::redo()
{
    repo->addMovie(M);
}

void AddOp::undo()
{
    repo->deleteMovie(M.getTitle(), M.getReleaseDate());
}
