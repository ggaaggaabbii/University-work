#include "include/UpdateOp.h"

UpdateOp::UpdateOp(Repository* r, Movie& m, Movie& oldm)
{
    repo = r;
    M = m;
    oldM = oldm;
}

void UpdateOp::redo()
{
    repo->updateMovie(oldM.getTitle(), oldM.getReleaseDate(), M);
}

void UpdateOp::undo()
{
    repo->updateMovie(M.getTitle(), M.getReleaseDate(), oldM);
}
