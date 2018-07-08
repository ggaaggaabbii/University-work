#pragma once

#include <bits/stdc++.h>
#include "solver.h"

class UserInterface
{
private:
	std::string fileName;

public:
	UserInterface(char *);
	~UserInterface();
	void start();
};