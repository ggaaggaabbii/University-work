#pragma once

#include "repository.h"
#include "undoController.h"

typedef struct {
	Repo* repo;
	UndoController* u;
} Controller;


/*
creates a new controller
intput: a repository, a link to the undo controller
output: a pointer to the new controller
*/
Controller* createController(Repo* r, UndoController*);

/*
destroys a controller
intput: a pointer to the controller
*/
void destroyController(Controller *c);

/*
adds a new element to the repository
intput: a pointer to the controller, a pointer to the offer
output: 1 if the addition could be done, 0 otherwise
*/
int addOffer(Controller *c, Offer* offer);

/*
outputs the size of a repository
intput: a pointer to the controller
output: the number of elements in it
*/
int sizeOfRepoCtrl(Controller *c);

/*
deletes an element from the repository
input: a pointer to the controller, the unique destination and departure date
output: 1 if the deletion took place, 0 otherwise
*/
int deleteOffer(Controller *c, char* destination, char* departureDate);

/*
replaces an element identified by the destination and departure date with a new element
input: a pointer to the controller, the destination, the departure date, a pointer to the new element
output: 1 if the element was found, 0 otherwise
*/
int updateOffer(Controller *c, char* destination, char* departureDate, void* newElement);

/*
builds a new sorted array from an initial array
input: the controller, a comparison function
output: a pointer to the new array
*/
void** sortOffers(Controller* c, void** v, int length, int (*cmp)(void*, void*));

/*
creates a list of offers that match with the destination, sorted ascending or descending
depending on the type and return the size of the newly formed array
input: the controller, the destination string, the type of the sorting (1/2), the adress of the result list
output: the size of the result list
*/
int displayOffersCtrl(Controller* c, char* destination, int type, void*** v);

/*
creates a list of offers that match with a filter function, sorted by a compare function
input: the controller, the filter function, the compare function, the adress of the result list
output: the size of the result list
*/
int displayOffersCtrl2(Controller* , int(*)(void*, char*, int), int (*)(void*, void*), void*** , char*, int);


/*
filters the offers with a given function and returns a list of pointers to the result
input: a pointer to a controller, a function that returns 1 if the given string is contained in one of the fields of the offer
output: a list of pointers to the elements that respect the filtering rule or NULL if there is no such element
*/
void filterOffers(Controller*, int(*)(void*, char*, int), void**, int*, char*, int);

/*
checks if the second string appears in the first one using the KMP algorithm
input: 2 strings
output: a pointer to the starting position of the second string from the first string, or NULL if the string was not found
*/
char* stingInString(char* str1, char* str2);

/*
performes an undo operation
input: a pointer to a controller
output: 1 if the operation took place or 0 otherwise
*/
int undoCtrl(Controller*);

/*
performes an redo operation
input: a pointer to a controller
output: 1 if the operation took place or 0 otherwise
*/
int redoCtrl(Controller*);