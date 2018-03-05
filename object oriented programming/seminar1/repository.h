#pragma once
#include "planet.h"

typedef struct {
	Planet *vect[100];
	int length;
} Repo;

Repo *createRepo();
void destroyRepo(Repo *r);
void addToRepo(Repo *r, Planet *p);