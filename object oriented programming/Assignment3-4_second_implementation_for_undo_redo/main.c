#include "offer.h"
#include "controller.h"
#include "repository.h"
#include "ui.h"

int main(void) {
	Repo* r = createRepo();
	UndoController* un = createUndoController(r);
	Controller* c = createController(r, un);
	Ui* u = createUi(c);
	start(u);
	destroyUi(u);
	return 0;
}