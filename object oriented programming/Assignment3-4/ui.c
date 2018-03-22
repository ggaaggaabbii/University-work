#include "ui.h"
#include "offer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void printMenu() {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
	       "Choose an option:",
	       "0. Exit",
	       "1. Add an offer",
	       "2. Delete an offer",
	       "3. Update an offer",
	       "4. Display offers sorted by the price",
	       "5. Display offers of a given type sorted by destination",
	       "6. Display offers of a given type starting from a given date",
	       "7. Display offers that are more expensive than a given price",
	       "8. Undo",
	       "9. Redo",
	       "10. Display offers of a given type less expensive than a given price"
	      );
}

Ui* createUi(Controller* ctrl) {
	Ui* u = (Ui*)malloc(sizeof(Ui));
	u->ctrl = ctrl;
	return u;
}

void destroyUi(Ui* u) {
	destroyController(u->ctrl);
	free(u);
}

static int validateDate(char* Date) {
	int v[] = {0, 1, 2, 3, 5, 6, 8, 9};
	if (strlen(Date) != 10)
		return 0;
	for (int i = 0; i < 8; ++i) {
		if (Date[v[i]] < '0' || Date[v[i]] > '9')
			return 0;
	}
	if (Date[4] != '-' || Date[7] != '-')
		return 0;
	int yy = atoi(Date), mm = atoi(Date + 5), dd = atoi(Date + 8);
	if (yy >= 1900 && yy <= 9999)
		if (mm >= 1 && mm <= 12) {
			if ((dd >= 1 && dd <= 31) && (mm == 1 || mm == 3 || mm == 5 || mm == 7 || mm == 8 || mm == 10 || mm == 12))
				return 1;
			else if ((dd >= 1 && dd <= 30) && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
				return 1;
			else if ((dd >= 1 && dd <= 28) && (mm == 2))
				return 1;
			else if (dd == 29 && mm == 2 && (yy % 400 == 0 || (yy % 4 == 0 && yy % 100 != 0)))
				return 1;
		}
	return 0;
}

static void addOfferUi(Ui * u) {
	char type[100], destination[100], departureDate[11];
	double price;
	printf("%s\n", "Introduce the type of the offer:");
	scanf("%s", type);
	printf("%s\n", "Introduce the destination of the offer:");
	scanf("%s", destination);
	printf("%s\n", "Introduce the departure date (yyyy-mm-dd) of the offer:");
	scanf("%s", departureDate);
	if (validateDate(departureDate) == 0) {
		printf("%s\n", "Invalid date!");
		return;
	}
	printf("%s\n", "Introduce the cost of the offer:");
	scanf("%lf", &price);
	Offer* o = createOffer(type, destination, departureDate, price);
	if (addOffer(u->ctrl, o) == 0) {
		printf("%s\n", "Error while adding the offer...");
		destroyOffer(o);
	}
}

static void deleteOfferUi(Ui * u) {
	char destination[100], departureDate[11];
	printf("%s\n", "Introduce the destination of the offer:");
	scanf("%s", destination);
	printf("%s\n", "Introduce the departure date (yyyy-mm-dd) of the offer:");
	scanf("%s", departureDate);
	if (deleteOffer(u->ctrl, destination, departureDate) == 0) {
		printf("%s\n", "Error while deleting the offer...");
	}
}

static void updateOfferUi(Ui * u) {
	char type[100], oldDestination[100], newDestination[100], newDepartureDate[11], oldDepartureDate[11];
	double price;
	printf("%s\n", "Introduce the old destination of the offer:");
	scanf("%s", oldDestination);
	printf("%s\n", "Introduce the old departure date (yyyy-mm-dd) of the offer:");
	scanf("%s", oldDepartureDate);
	printf("%s\n", "Introduce the new type of the offer:");
	scanf("%s", type);
	printf("%s\n", "Introduce the new destination of the offer:");
	scanf("%s", newDestination);
	printf("%s\n", "Introduce the new departure date (yyyy-mm-dd) of the offer:");
	scanf("%s", newDepartureDate);
	if (validateDate(newDepartureDate) == 0) {
		printf("%s\n", "Invalid date!");
		return;
	}
	printf("%s\n", "Introduce the new cost of the offer:");
	scanf("%lf", &price);
	Offer* o = createOffer(type, newDestination, newDepartureDate, price);
	if (updateOffer(u->ctrl, oldDestination, oldDepartureDate, o) == 0) {
		printf("%s\n", "Error while updating the offer...");
		destroyOffer(o);
	}
}

static void show(Offer * o) {
	printf("\n%s :%s\n%s :%s\n%s :%s\n%s :%lf\n\n",
	       "Destination",
	       o->destination,
	       "Type",
	       o->type,
	       "Departure date",
	       o->departureDate,
	       "Price",
	       o->price
	      );
}

static void displayOffersUi(Ui * u) {
	char* destination = (char*)malloc(sizeof(char) * 100);
	size_t size = 99;
	printf("%s\n", "Introduce the destination you are looking for (empty string will display all):");
	getline(&destination, &size, stdin);
	getline(&destination, &size, stdin);
	destination[strlen(destination) - 1] = '\0';
	printf("%s\n%s\n%s\n",
	       "Introduce the type of sorting:",
	       "1. Asscending",
	       "2. Descending");
	char sortType[10];
	int sortTypeForList;
	scanf("%s", sortType);
	if (strcmp(sortType, "1") == 0) sortTypeForList = 1;
	else if (strcmp(sortType, "2") == 0) sortTypeForList = 2;
	else {printf("%s\n", "Invalid input!"); free(destination); return;}
	void** v;
	int length = displayOffersCtrl(u->ctrl, destination, sortTypeForList, &v);
	if (length == 0) {
		printf("%s\n", "List is empty!");
	}
	for (int i = 0; i < length; ++i) {
		Offer* o = v[i];
		show(o);
	}
	if (length) free(v);
	free(destination);
}

static void populateRepo(Ui * u) {
	Offer* o = createOffer("seaside", "Madrid", "2018-04-12", 345);
	addOffer(u->ctrl, o);
	o = createOffer("seaside", "Madrid", "2018-05-12", 365);
	addOffer(u->ctrl, o);
	o = createOffer("mountain", "Madrid", "2018-06-12", 325);
	addOffer(u->ctrl, o);
	o = createOffer("seaside", "Madrid", "2018-02-12", 315);
	addOffer(u->ctrl, o);
	o = createOffer("seaside", "Barcelona", "2018-05-12", 450);
	addOffer(u->ctrl, o);
	o = createOffer("city-break", "Barcelona", "2018-06-14", 212);
	addOffer(u->ctrl, o);
	o = createOffer("seaside", "London", "2018-01-19", 330);
	addOffer(u->ctrl, o);
	o = createOffer("city-break", "Bucharest", "2018-02-20", 130);
	addOffer(u->ctrl, o);
}

int filterByType(void* o, char* type, int r) {
	Offer *o2 = o;
	if (strcmp(o2->type, type) == 0)
		return 1;
	return 0;
}

int compareByDestination(void* a, void* b) {
	Offer *a1 = a, *b1 = b;
	if (strcmp(a1->destination, b1->destination) <= 0)
		return 1;
	return 0;
}

int filterByTypeAndDate(void* o, char* type, int date) {
	Offer *o2 = o;
	if (strcmp(o2->type, type) == 0)
		if (atoi(o2->departureDate) * 10000 + atoi(o2->departureDate + 5) * 100 + atoi(o2->departureDate + 9) >= date)
			return 1;
	return 0;
}

int filterByPrice(void* o, char* type, int price) {
	Offer *o2 = o;
	if (o2->price >= price)
		return 1;
	return 0;
}

static void displayOffersUiByType(Ui *u) {
	char* type = (char*)malloc(sizeof(char) * 100);

	printf("%s\n", "Introduce the type of the offer:");
	scanf("%s", type);

	void** v;
	int length = displayOffersCtrl2(u->ctrl, filterByType, compareByDestination, &v, type, 0);

	if (length == 0) {
		printf("%s\n", "List is empty!");
	}
	for (int i = 0; i < length; ++i) {
		Offer* o = v[i];
		show(o);
	}
	if (length) free(v);

	free(type);
	return;
}


static void displayOffersUiByTypeAndDate(Ui *u) {
	char* type = (char*)malloc(sizeof(char) * 100);
	char departureDate[11];

	printf("%s\n", "Introduce the type of the offer:");
	scanf("%s", type);
	printf("%s\n", "Introduce the departure date (yyyy-mm-dd):");
	scanf("%s", departureDate);
	if (validateDate(departureDate) == 0) {
		printf("%s\n", "Invalid date!");
		return;
	}

	int a = atoi(departureDate) * 10000 + atoi(departureDate + 5) * 100 + atoi(departureDate + 9);

	void** v;
	int length = displayOffersCtrl2(u->ctrl, filterByTypeAndDate, compareByDestination, &v, type, a);

	if (length == 0) {
		printf("%s\n", "List is empty!");
	}
	for (int i = 0; i < length; ++i) {
		Offer* o = v[i];
		show(o);
	}
	if (length) free(v);

	free(type);
	return;
}

static void displayOffersUiByPrice(Ui *u) {
	int price;

	printf("%s\n", "Introduce the price of the offer:");
	scanf("%d", &price);

	void** v;
	int length = displayOffersCtrl2(u->ctrl, filterByPrice, compareByDestination, &v, NULL, price);

	if (length == 0) {
		printf("%s\n", "List is empty!");
	}
	for (int i = 0; i < length; ++i) {
		Offer* o = v[i];
		show(o);
	}
	if (length) free(v);
	return;
}

int filterByTypeAndPrice(void* o, char* type, int price) {
	Offer *o2 = o;
	if (strcmp(o2->type, type) == 0)
		if (o2->price <= price)
			return 1;
	return 0;
}

static void displayOffersUiByTypeAndPrice(Ui *u) {
	char* type = (char*)malloc(sizeof(char) * 100);
	int price;

	printf("%s\n", "Introduce the type of the offer:");
	scanf("%s", type);
	printf("%s\n", "Introduce the maximum price of the offer:");
	scanf("%d", &price);

	void** v;
	int length = displayOffersCtrl2(u->ctrl, filterByTypeAndPrice, compareByDestination, &v, type, price);

	if (length == 0) {
		printf("%s\n", "List is empty!");
	}
	for (int i = 0; i < length; ++i) {
		Offer* o = v[i];
		show(o);
	}
	if (length) free(v);

	free(type);
	return;
}

void undoUi(Ui *u) {
	if (undoCtrl(u->ctrl) == 0) {
		printf("%s\n", "Already the earliest version!");
		return;
	}
	printf("%s\n", "Succesfully did the undo operation!");
}

void redoUi(Ui *u) {
	if (redoCtrl(u->ctrl) == 0) {
		printf("%s\n", "Already the latest version!");
		return;
	}
	printf("%s\n", "Succesfully did the redo operation!");
}

void start(Ui * u) {
	char* command = (char*)malloc(sizeof(char) * 100);
	populateRepo(u);
	while (1) {
		printMenu();
		scanf("%s", command);
		if (strcmp(command, "0") == 0) {
			free(command);
			return;
		} else if (strcmp(command, "1") == 0) {
			addOfferUi(u);
		} else if (strcmp(command, "2") == 0) {
			deleteOfferUi(u);
		} else if (strcmp(command, "3") == 0) {
			updateOfferUi(u);
		} else if (strcmp(command, "4") == 0) {
			displayOffersUi(u);
		} else if (strcmp(command, "5") == 0) {
			displayOffersUiByType(u);
		} else if (strcmp(command, "6") == 0) {
			displayOffersUiByTypeAndDate(u);
		} else if (strcmp(command, "7") == 0) {
			displayOffersUiByPrice(u);
		} else if (strcmp(command, "8") == 0) {
			undoUi(u);
		} else if (strcmp(command, "9") == 0) {
			redoUi(u);
		} else if (strcmp(command, "10") == 0) {
			displayOffersUiByTypeAndPrice(u);
		} else {
			printf("%s\n", "Invalid command!");
		}
	}
}