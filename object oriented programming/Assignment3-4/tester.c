#include "offer.h"
#include "repository.h"
#include "controller.h"
#include "undoController.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void testOffer(char* type, char* destination, char* departureDate, double price) {
	Offer* o = createOffer(type, destination, departureDate, price);
	assert(strcmp(o->type, type) == 0);
	assert(strcmp(o->destination, destination) == 0);
	assert(strcmp(o->departureDate, departureDate) == 0);
	assert(o->price == price);
	Offer *of = createCopyOffer(o);
	destroyOffer(of);
	destroyOffer(o);
}

void testRepo() {
	Repo* r = createRepo();

	assert(sizeOfRepo(r) == 0);

	Offer* o = createOffer("seaside", "Madrid", "2018-04-12", 345);

	assert(addElemet(r, o) == 1);
	assert(addElemet(r, o) == 0);
	Offer* q = r->array[0];

	assert(strcmp(q->destination, "Madrid") == 0);
	assert(strcmp(q->departureDate, "2018-04-12") == 0);
	assert(strcmp(q->type, "seaside") == 0);
	assert(q->price == 345);

	assert(deleteElemet(r, "Madrid", "2018-04-13") == 0);
	assert(deleteElemet(r, "Madrid", "2018-04-12") == 1);
	assert(sizeOfRepo(r) == 0);

	o = createOffer("seaside", "Madrid", "2018-04-12", 345);
	assert(addElemet(r, o) == 1);

	q = createOffer("seaside", "Barcelona", "2018-04-12", 345);

	assert(updateElement(r, "Madrid", "2018-04-12", q) == 1);
	assert(deleteElemet(r, "Barcelona", "2018-04-12") == 1);


	destroyRepo(r);
}

void testController() {
	Repo* r = createRepo();
	UndoController* u = createUndoController(r);
	Controller* c = createController(r, u);

	Offer* o = createOffer("seaside", "Madrid", "2018-04-12", 345);

	assert(addOffer(c, o) == 1);
	assert(addOffer(c, o) == 0);
	Offer* q = r->array[0];

	assert(strcmp(q->destination, "Madrid") == 0);
	assert(strcmp(q->departureDate, "2018-04-12") == 0);
	assert(strcmp(q->type, "seaside") == 0);
	assert(q->price == 345);

	assert(deleteOffer(c, "Madrid", "2018-04-13") == 0);
	assert(deleteOffer(c, "Madrid", "2018-04-12") == 1);
	assert(undoCtrl(c) == 1);
	assert(redoCtrl(c) == 1);
	assert(sizeOfRepoCtrl(c) == 0);

	o = createOffer("seaside", "Madrid", "2018-04-12", 345);
	assert(addOffer(c, o) == 1);
	assert(undoCtrl(c) == 1);
	assert(redoCtrl(c) == 1);
	assert(redoCtrl(c) == 0);

	q = createOffer("seaside", "Barcelona", "2018-04-12", 345);

	assert(updateOffer(c, "Madrid", "2018-04-12", q) == 1);
	assert(deleteOffer(c, "Barcelona", "2018-04-12") == 1);
	assert(undoCtrl(c) == 1);
	assert(redoCtrl(c) == 1);
	assert(redoCtrl(c) == 0);

	destroyController(c);
}

int compareOffers(void* a, void* b) {
	Offer *a1 = a, *b1 = b;
	if (a1->price < b1->price)
		return 1;
	return 0;
}

void testControllerSort() {
	Repo* r = createRepo();
	UndoController* u = createUndoController(r);
	Controller* c = createController(r, u);

	Offer* o = createOffer("seaside", "Madrid", "2018-04-12", 345);
	assert(addOffer(c, o) == 1);
	o = createOffer("seaside", "Madrid", "2018-05-12", 365);
	assert(addOffer(c, o) == 1);
	o = createOffer("seaside", "Madrid", "2018-06-12", 325);
	assert(addOffer(c, o) == 1);
	o = createOffer("seaside", "Madrid", "2018-02-12", 315);
	assert(addOffer(c, o) == 1);

	undoCtrl(c);
	redoCtrl(c);
	undoCtrl(c);
	undoCtrl(c);

	void** offers = sortOffers(c, c->repo->array, c->repo->length, compareOffers);
	int v[] = {345, 365};
	for (int i = 0; i < 2; ++i) {
		o = offers[i];
		assert(o->price == v[i]);
	}
	free(offers);



	int l = displayOffersCtrl(c, "Madrid", 1, &offers);
	assert(l == 2);
	for (int i = 0; i < 2; ++i) {
		o = offers[i];
		assert(o->price == v[i]);
	}
	free(offers);

	destroyController(c);
}

int filterByDest(void* o, char* dest, int r) {
	Offer *o2 = o;
	if (strcmp(o2->destination, dest) == 0)
		return 1;
	return 0;
}

void testController3() {
	Repo* r = createRepo();
	UndoController* u = createUndoController(r);
	Controller* c = createController(r, u);

	Offer* o = createOffer("seaside", "Madrid", "2018-04-12", 345);
	assert(addOffer(c, o) == 1);
	o = createOffer("seaside", "Madrid", "2018-05-12", 365);
	assert(addOffer(c, o) == 1);
	o = createOffer("seaside", "Madrid", "2018-06-12", 325);
	assert(addOffer(c, o) == 1);
	o = createOffer("seaside", "Madrid", "2018-02-12", 315);
	assert(addOffer(c, o) == 1);

	undoCtrl(c);

	void** offers;
	int l = displayOffersCtrl2(c, filterByDest, compareOffers , &offers, "Madrid", 0);

	int v[] = {325, 345, 365};

	assert(l == 3);
	for (int i = 0; i < 3; ++i) {
		o = offers[i];
		assert(o->price == v[i]);
	}
	free(offers);

	destroyController(c);

}

void testKMP() {
	assert(stingInString("abracadabra", "abra") != NULL);
	assert(stingInString("aaaaa", "a") != NULL);
	assert(stingInString("babababaa", "baa") != NULL);
	assert(stingInString("babababa", "baa") == NULL);
	assert(stingInString("aaa", "aaa") != NULL);
}

void testOperation() {
	Offer *offer = createOffer("seaside", "Madrid", "2018-05-12", 365);
	Operation * o = createOperation(offer, "Madrid", "2018-05-12", "Add", "Delete", "", 0);
	assert(strcmp(o->typeOfOperationDo, "Add") == 0);
	assert(o->o == offer);
	destroyOperation(o);
}


int main() {
	testOffer("seaside", "Madrid", "2018-04-12", 345);
	testOffer("montain", "Rome", "2018-05-31", 450);
	testOffer("city-break", "Paris", "2018-03-22", 235);
	testRepo();
	testController();
	testKMP();
	testControllerSort();
	testController3();
	testOperation();
	return 0;
}