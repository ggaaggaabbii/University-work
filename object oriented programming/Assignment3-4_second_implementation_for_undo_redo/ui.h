#pragma once
#include "controller.h"
#include "offer.h"

typedef struct {
	Controller* ctrl;
} Ui;

/*
creates a new user interface
input: the controller
output: a pointer to the user interface object
*/
Ui* createUi(Controller* ctrl);

/*
destroys the user interface object
input: a pointer to the user interface that needs to be destroyed
*/
void destroyUi(Ui* u);

/*
starts the ui
*/
void start(Ui* u);