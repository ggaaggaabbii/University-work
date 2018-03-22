#include "repository.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Repo* createRepo() {
	Repo* r = (Repo*)malloc(sizeof(Repo));
	r->length = 0;
	r->capacity = 10;
	r->array = (void**)malloc(sizeof(void*) * r->capacity);
	return r;
}

void destroyRepo(Repo *r) {
	free(r->array);
	free(r);
}

int addElemet(Repo *r, void* element) {
	Offer* x;
	Offer* newElement = element;
	for (int i = 0; i < r->length; ++i) {
		x = r->array[i];
		if (strcmp(x->destination, newElement->destination) == 0 &&
		        strcmp(x->departureDate, newElement->departureDate) == 0) {
			return 0;
		}
	}

	if (r->length == r->capacity) {
		r->capacity *= 2;
		r->array = realloc(r->array, sizeof(void*) * r->capacity);
	}
	r->array[r->length++] = element;
	return 1;
}

int deleteElemet(Repo *r, char* destination, char* departureDate) {
	Offer *x;
	for (int i = 0; i < r->length; ++i) {
		x = r->array[i];
		if (strcmp(x->destination, destination) == 0 && strcmp(x->departureDate, departureDate) == 0) {
			destroyOffer(x);
			r->array[i] = r->array[--r->length];
			if (r->capacity > 10 && r->length == r->capacity / 4) {
				r->capacity /= 2;
				r->array = realloc(r->array, sizeof(void*) * r->capacity);
			}
			return 1;
		}
	}
	return 0;
}

int updateElement(Repo *r, char* destination, char* departureDate, void* newElement) {
	Offer *x;
	for (int i = 0; i < r->length; ++i) {
		x = r->array[i];
		if (strcmp(x->destination, destination) == 0 && strcmp(x->departureDate, departureDate) == 0) {
			destroyOffer(x);
			r->array[i] = newElement;
			return 1;
		}
	}
	return 0;
}

int sizeOfRepo(Repo* r) {
	return r->length;
}

void* find(Repo *r, char* destination, char* departureDate) {
	Offer *x;
	for (int i = 0; i < r->length; ++i) {
		x = r->array[i];
		if (strcmp(x->destination, destination) == 0 && strcmp(x->departureDate, departureDate) == 0) {
			return x;
		}
	}
	return 0;
}

Repo* createCopyRepo(Repo* repo) {
	Repo* r = (Repo*)malloc(sizeof(Repo));
	r->length = repo->length;
	r->capacity = repo->capacity;
	r->array = (void**)malloc(sizeof(void*) * r->capacity);
	for (int i = 0; i < r->length; ++i) {
		r->array[i] = createCopyOffer(repo->array[i]);
	}
	return r;
}