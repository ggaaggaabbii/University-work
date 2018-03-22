#include "offer.h"
#include <stdlib.h>
#include <string.h>

Offer* createOffer(char* type, char* destination, char* departureDate, double price) {
	Offer *o = (Offer*)malloc(sizeof(Offer));

	o->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(o->type, type);

	o->destination = (char*)malloc(sizeof(char) * (strlen(destination) + 1));
	strcpy(o->destination, destination);

	o->departureDate = (char*)malloc(sizeof(char) * (strlen(departureDate) + 1));
	strcpy(o->departureDate, departureDate);

	o->price = price;

	return o;
}

void destroyOffer(Offer* o) {
	free(o->type);
	free(o->destination);
	free(o->departureDate);
	free(o);
}

Offer* createCopyOffer(Offer* offer) {
	Offer *o = (Offer*)malloc(sizeof(Offer));

	o->type = (char*)malloc(sizeof(char) * (strlen(offer->type) + 1));
	strcpy(o->type, offer->type);

	o->destination = (char*)malloc(sizeof(char) * (strlen(offer->destination) + 1));
	strcpy(o->destination, offer->destination);

	o->departureDate = (char*)malloc(sizeof(char) * (strlen(offer->departureDate) + 1));
	strcpy(o->departureDate, offer->departureDate);

	o->price = offer->price;

	return o;
}