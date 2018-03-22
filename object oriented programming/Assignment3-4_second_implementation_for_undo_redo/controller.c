#include "controller.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Controller* createController(Repo* r, UndoController* u) {
	Controller* c = (Controller*)malloc(sizeof(Controller));
	c->repo = r;
	c->u = u;
	return c;
}

void destroyController(Controller *c) {
	/*
	for (int i = 0; i < c->repo->length; ++i) {
		destroyOffer(c->repo->array[i]);
	}
	*/
	destroyUndoController(c->u);
	//destroyRepo(c->repo);
	free(c);
}

int addOffer(Controller *c, Offer* offer) {
	return addElemetUndoController(c->u, offer, &(c->repo));
}

int sizeOfRepoCtrl(Controller *c) {
	return sizeOfRepo(c->repo);
}

int deleteOffer(Controller *c, char* destination, char* departureDate) {
	return deleteElemetUndoController(c->u, destination, departureDate, &(c->repo));
}

int updateOffer(Controller *c, char* destination, char* departureDate, void* newElement) {
	return updateElementUndoController(c->u, destination, departureDate, newElement, &(c->repo));
}

int compareAscending(void* a, void* b) {
	Offer *a1 = a, *b1 = b;
	if (a1->price < b1->price)
		return 1;
	return 0;
}

int compareDescending(void* a, void* b) {
	Offer *a1 = a, *b1 = b;
	if (a1->price > b1->price)
		return 1;
	return 0;
}

void merge(void** v, int l, int r, int (*cmp)(void*, void*)) {
	int mid = (l + r) / 2;
	int length1 = mid - l + 1;
	int length2 = r - mid;
	int counter1 = 0, counter2 = 0, counter = 0;
	void **newArray = (void**)malloc(sizeof(void*) * (length1 + length2));
	while (counter1 < length1 && counter2 < length2) {
		Offer *a, *b;
		a = v[l + counter1];
		b = v[mid + 1 + counter2];
		if (cmp(a, b)) {
			newArray[counter++] = a;
			++counter1;
		} else {
			newArray[counter++] = b;
			++counter2;
		}
	}
	while (counter1 < length1) {
		Offer* a = v[l + counter1];
		newArray[counter++] = a;
		++counter1;
	}
	while (counter2 < length2) {
		Offer* a = v[mid + 1 + counter2];
		newArray[counter++] = a;
		++counter2;
	}
	for (int i = l; i <= r; ++i) {
		v[i] = newArray[i - l];
	}
	free(newArray);
}

void sort(void** v, int l, int r, int (*cmp)(void*, void*)) {
	if (r <= l)
		return;
	int mid = (l + r) / 2;
	sort(v, l, mid, cmp);
	sort(v, mid + 1, r, cmp);
	merge(v, l, r, cmp);
}

void** sortOffers(Controller* c, void **v, int length, int (*cmp)(void*, void*)) {
	void** x = (void**)malloc(sizeof(void*) * length);
	for (int i = 0; i < length; ++i) {
		x[i] = v[i];
	}

	sort(x, 0, length - 1, cmp);
	if (length == 0)
		free(x);
	return x;
}

void build(int* p, char* str, int size) {
	memset(p, 0, sizeof(int) * size);
	int k = -1;
	p[0] = -1;
	for (int i = 1; i < size; ++i) {
		while (k > -1 && str[i] != str[k + 1])
			k = p[k];
		if (str[i] == str[k + 1])
			++k;
		p[i] = k;
	}
}

char* stingInString(char* str1, char* str2) {
	int n = strlen(str1);
	int m = strlen(str2);
	int* p = (int*)malloc(sizeof(int) * m);
	build(p, str2, m);
	int k = -1;
	for (int i = 0; i < n; ++i) {
		while (k > -1 && str1[i] != str2[k + 1]) {
			k = p[k];
		}
		if (str2[k + 1] == str1[i]) {
			++k;
		}
		if (k == m - 1) {
			free(p);
			return str1 + i - m;
		}
	}
	free(p);
	return NULL;
}

int displayOffersCtrl(Controller* c, char* destination, int type, void*** v) {
	void** newArray = (void*)malloc(c->repo->length * sizeof(void*));
	int length = 0;
	for (int i = 0; i < c->repo->length; ++i) {
		Offer* o = c->repo->array[i];
		if (strlen(destination) == 0 || stingInString(o->destination, destination) != NULL) {
			newArray[length++] = c->repo->array[i];
		}
	}

	void** resultArray;
	if (length) {
		if (type == 1) {
			resultArray = sortOffers(c, newArray, length, compareAscending);
		} else if (type == 2) {
			resultArray = sortOffers(c, newArray, length, compareDescending);
		} else {
			return -1;
		}
	}
	*v = resultArray;
	free(newArray);
	return length;
}

void filterOffers(Controller* c, int(*filter)(void*, char*, int), void** result, int* length, char* stringForFilter, int integerForFilter) {
	for (int i = 0; i < c->repo->length; ++i) {
		if (filter(c->repo->array[i], stringForFilter, integerForFilter)) {
			result[*length] = c->repo->array[i];
			*length += 1;
		}
	}
}

int displayOffersCtrl2(Controller* c, int(*filterFunction)(void*, char*, int), int (*cmpFunction)(void*, void*), void*** v, char* stringForFilter, int integerForFilter) {
	void** newArray = (void*)malloc(c->repo->length * sizeof(void*));
	int length = 0;
	filterOffers(c, filterFunction, newArray, &length, stringForFilter, integerForFilter);
	void** resultArray = sortOffers(c, newArray, length, cmpFunction);
	*v = resultArray;
	free(newArray);
	return length;
}

int undoCtrl(Controller* c) {
	return undo(c->u, &(c->repo));
}

int redoCtrl(Controller* c) {
	return redo(c->u, &(c->repo));
}