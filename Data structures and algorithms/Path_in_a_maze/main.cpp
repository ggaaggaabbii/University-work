#include <bits/stdc++.h>
#include "Queue.h"
#include "PriorityQueue.h"
#include "tester.h"
#include "userInterface.h"
#define pb push_back
#define mp make_pair
#define sec second
#define fir first
#define INF 1000000000

using namespace std;

int main(int ac, char** av) {
	smallTestQueue();
	smallTestPQ();

	if (ac < 2) {
		cout << "Usage: .exe [file]\n";
		return 0;
	}

	UserInterface u{av[1]};
	u.start();

	return 0;
}