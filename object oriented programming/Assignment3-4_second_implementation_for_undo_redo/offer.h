#pragma once

typedef struct {
	char* type;
	char* destination;
	char* departureDate;
	double price;
} Offer;

/*
creates a new offer
intput: 3 strings and a double (the type, the destination, the departure date and the price)
output: a pointer to the newly created offer
*/
Offer* createOffer(char* type, char* destination, char* departureDate, double price);

/*
destroys an offer and frees the memory
input: a pointer to an offer
*/
void destroyOffer(Offer* o);

/*
creates a copy of a given offer
input: a pointer to an offer
output: a pointer to a copy of the offer
*/
Offer* createCopyOffer(Offer*);