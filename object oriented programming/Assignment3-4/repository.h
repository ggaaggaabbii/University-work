#pragma once
#include "offer.h"

typedef struct {
	int length;
	int capacity;
	void** array;
} Repo;

/*
creates a new repository
output: a pointer to the new repository
*/
Repo* createRepo();

/*
destroys a repository
*/
void destroyRepo(Repo *r);

/*
adds a new element to the repository
intput: a pointer to the repository, a pointer to the element
output: 1 if the addition could be done, 0 otherwise
*/
int addElemet(Repo *r, void* element);

/*
outputs the size of a repository
intput: a pointer to the repository
output: the number of elements in it
*/
int sizeOfRepo(Repo *r);

/*
deletes an element from the repository
input: a pointer to the repository, the unique destination and departure date
output: 1 if the deletion took place, 0 otherwise
*/
int deleteElemet(Repo *r, char* destination, char* departureDate);

/*
replaces an element identified by the destination and departure date with a new element
input: a pointer to the repository, the destination, the departure date, a pointer to the new element
output: 1 if the element was found, 0 otherwise
*/
int updateElement(Repo *r, char* destination, char* departureDate, void* newElement);

/*
searches for an element in the repository
input: a pointer to a repository, a destination string, a departure date string
output: a pointer to the element if it is in the list, or NULL otherwise
*/
void* find(Repo *r, char* destination, char* departureDate);