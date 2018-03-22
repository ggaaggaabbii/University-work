#pragma once
#include "repository.h"
#include <string.h>
#include <stdlib.h>

typedef struct {
	Repo** repos;
	int size;
	int index;
	int capacity;
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
adds a new element to the newly created repository which is a copy of the last one
input: a pointer to the undo controller, a pointer to an offer, a pointer to the current repository
output: 1 if the operation could be done, 0 otherwise
*/
int addElemetUndoController(UndoController*, Offer*, Repo**);

/*
delets an element of the newly created repository which is a copy of the last one
input: a pointer to the undo controller, a destination, a departure date, a pointer to the current repository
output: 1 if the operation could be done, 0 otherwise
*/
int deleteElemetUndoController(UndoController*, char*, char*, Repo**);

/*
updates an element of the newly created repository which is a copy of the last one
input: a pointer to the undo controller, a destination, a departure date, a pointer to the offer, a pointer to the current repository
output: 1 if the operation could be done, 0 otherwise
*/
int updateElementUndoController(UndoController*, char*, char*, Offer*, Repo**);

/*
performes an undo operation
input: a pointer to an undo controller, and the current repository
output: 1 if the operation took place or 0 otherwise
*/
int undo(UndoController*, Repo**);

/*
performes an redo operation
input: a pointer to an undo controller, and the current repository
output: 1 if the operation took place or 0 otherwise
*/
int redo(UndoController*, Repo**);