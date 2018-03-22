#pragma once
#include "repository.h"
#include <string.h>
#include <stdlib.h>


typedef struct {
	Offer *o;
	char* destination;
	char* departureDate;
	char* type;
	char* typeOfOperationDo;
	char* typeOfOperationUndo;
	double price;

} Operation;

/*
creates a new operation for a given offer and a given type
input: a pointer to an offer, a string representing the type of operation
output: a pointer to the newly created operation
*/
Operation* createOperation(Offer*, char*, char*, char*, char*, char*, double);

/*
destroys an operation and frees all the memory coresponding to the operation
input: a pointer to the operation
*/
void destroyOperation(Operation*);

//======================================================================

typedef struct {
	Operation** operationStack;
	int index;
	int size;
	int capacity;
	Repo* repo;
} UndoController;


/*
creates a new undo controller
input: a pointer to the current repository
output: a pointer to the newly created undo controller
*/
UndoController* createUndoController(Repo*);

/*
destroys an undo controller
input: a pointer to the undo controller
*/
void destroyUndoController(UndoController*);

/*
adds a new operation to the operation stack
input: a pointer to the undo controller, a pointer to the operation
*/
void addOperation(UndoController*, Operation*);

/*
performes an undo operation
input: a pointer to an undo controller
output: 1 if the operation took place or 0 otherwise
*/
int undo(UndoController*);

/*
performes an redo operation
input: a pointer to an undo controller
output: 1 if the operation took place or 0 otherwise
*/
int redo(UndoController*);