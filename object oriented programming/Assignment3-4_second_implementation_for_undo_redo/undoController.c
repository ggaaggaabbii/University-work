#include "undoController.h"

UndoController* createUndoController(Repo *r) {
	UndoController* u = (UndoController*)malloc(sizeof(UndoController));
	u->index = 0;
	u->size = 1;
	u->capacity = 100;
	u->repos = (Repo**)malloc(sizeof(Repo*) * u->capacity);
	u->repos[0] = r;
	return u;
}

void destroyUndoController(UndoController *u) {
	for (int i = 0; i < u->size; ++i) {
		for (int j = 0; j < u->repos[i]->length; ++j) {
			destroyOffer(u->repos[i]->array[j]);
		}
		destroyRepo(u->repos[i]);
	}
	free(u->repos);
	free(u);
}

void renewRepo(UndoController *u) {
	for (int i = u->index + 1; i < u->size; ++i) {
		for (int j = 0; j < u->repos[i]->length; ++j) {
			destroyOffer(u->repos[i]->array[j]);
		}
		destroyRepo(u->repos[i]);
	}
}

int addElemetUndoController(UndoController* u, Offer* o, Repo** r) {
	if (find(u->repos[u->index], o->destination, o->departureDate) == 0) {
		renewRepo(u);
		u->index++;
		u->repos[u->index] = createCopyRepo(u->repos[u->index - 1]);
		u->size = u->index + 1;
		addElemet(u->repos[u->index], o);
		*r = u->repos[u->index];
		return 1;
	}
	return 0;
}
int deleteElemetUndoController(UndoController* u, char* destination, char* departureDate, Repo** r) {
	if (find(u->repos[u->index], destination, departureDate) != 0) {
		renewRepo(u);
		u->index++;
		u->repos[u->index] = createCopyRepo(u->repos[u->index - 1]);
		u->size = u->index + 1;
		deleteElemet(u->repos[u->index], destination, departureDate);
		*r = u->repos[u->index];
		return 1;
	}
	return 0;
}
int updateElementUndoController(UndoController* u, char* destination, char* departureDate, Offer* newElement, Repo** r) {
	if (find(u->repos[u->index], destination, departureDate) != 0) {
		renewRepo(u);
		u->index++;
		u->repos[u->index] = createCopyRepo(u->repos[u->index - 1]);
		u->size = u->index + 1;
		updateElement(u->repos[u->index], destination, departureDate, newElement);
		*r = u->repos[u->index];
		return 1;
	}
	return 0;
}

int undo(UndoController *u, Repo** repo) {
	if (u->index > 0) {
		u->index--;
		*repo = u->repos[u->index];
		return 1;
	}
	return 0;
}

int redo(UndoController *u, Repo** repo) {
	if (u->index == u->size - 1)
		return 0;
	u->index++;
	*repo = u->repos[u->index];
	return 1;
}