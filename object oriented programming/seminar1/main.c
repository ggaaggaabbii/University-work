#include <stdio.h>
#include "planet.h"
#include "repository.h"

int main() {
	Planet *p = createPlanet("jupiter", "mare jupan", 20.9);
	printf("%s\n", getName(p));

	Repo *r = createRepo();
	addToRepo(r, p);
	printf("%s\n", getName(r->vect[0]));
	printf("%d\n", r->length);

	destroyRepo(r);
	return 0;
}