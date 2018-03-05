#include <stdlib.h>
#include "repository.h"

Repo *createRepo() {
	Repo *r = (Repo*)malloc(sizeof(Repo));
	r->length = 0;
	return r;
}

void destroyRepo(Repo *r) {
	for (int i = 0; i < r->length; ++i) {
		destroyPlanet(r->vect[i]);
	}
	free(r);
}

void addToRepo(Repo *r, Planet *p) {
	r->vect[r->length++] = p;
}