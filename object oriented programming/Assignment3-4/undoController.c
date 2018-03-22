#include "undoController.h"

Operation* createOperation(Offer* o, char* destination, char* departureDate, char* type, char* typeUndo, char* typeOfOffer, double price) {
	Operation *op = (Operation*)malloc(sizeof(Operation));
	op->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
	strcpy(op->destination, destination);
	op->departureDate = (char*)malloc(sizeof(char) * (strlen(departureDate) + 1));
	strcpy(op->departureDate, departureDate);
	op->typeOfOperationDo = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(op->typeOfOperationDo, type);
	op->typeOfOperationUndo = (char*)malloc(sizeof(char) * (strlen(typeUndo) + 1));
	strcpy(op->typeOfOperationUndo, typeUndo);

	op->type = (char*)malloc(sizeof(char) * (strlen(typeOfOffer) + 1));
	strcpy(op->type, typeOfOffer);
	op->price = price;

	op->o = o;
	return op;
}

void destroyOperation(Operation* op) {
	destroyOffer(op->o);
	free(op->destination);
	free(op->departureDate);
	free(op->typeOfOperationDo);
	free(op->typeOfOperationUndo);
	free(op->type);
	free(op);
}

UndoController* createUndoController(Repo *r) {
	UndoController* u = (UndoController*)malloc(sizeof(UndoController));
	u->index = 0;
	u->size = 0;
	u->capacity = 100;
	u->operationStack = (Operation**)malloc(sizeof(Operation) * u->capacity);
	u->repo = r;

	return u;
}

void destroyUndoController(UndoController *u) {
	for (int i = 0; i < u->size; ++i) {
		destroyOperation(u->operationStack[i]);
	}
	free(u->operationStack);
	free(u);
}

void addOperation(UndoController *u, Operation *op) {
	for (int i = u->index; i < u->size; ++i) {
		destroyOperation(u->operationStack[i]);
	}
	u->operationStack[u->index++] = op;
	u->size = u->index;
}

int undo(UndoController *u) {
	if (u->index == 0)
		return 0;
	u->index--;
	if (strcmp(u->operationStack[u->index]->typeOfOperationUndo, "Delete") == 0) {
		deleteElemet(u->repo, u->operationStack[u->index]->destination, u->operationStack[u->index]->departureDate);
	} else if (strcmp(u->operationStack[u->index]->typeOfOperationUndo, "Add") == 0) {
		addElemet(u->repo, createCopyOffer(u->operationStack[u->index]->o));
	} else {
		Operation *op = u->operationStack[u->index];
		updateElement(u->repo, op->o->destination, op->o->departureDate,
		              createOffer(op->type, op->destination, op->departureDate, op->price));
	}
	return 1;
}

int redo(UndoController *u) {
	if (u->index == u->size)
		return 0;
	if (strcmp(u->operationStack[u->index]->typeOfOperationDo, "Add") == 0) {
		addElemet(u->repo, createCopyOffer(u->operationStack[u->index]->o));
	} else if (strcmp(u->operationStack[u->index]->typeOfOperationDo, "Delete") == 0) {
		deleteElemet(u->repo, u->operationStack[u->index]->destination, u->operationStack[u->index]->departureDate);
	} else {
		updateElement(u->repo, u->operationStack[u->index]->destination,
		              u->operationStack[u->index]->departureDate,
		              createCopyOffer(u->operationStack[u->index]->o));
	}
	u->index++;
	return 1;
}