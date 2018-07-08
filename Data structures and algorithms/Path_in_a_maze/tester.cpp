#include "tester.h"

void smallTestQueue() {
	Queue<int> q;
	assert(q.isEmpty());
	for (int i = 0; i < 15; ++i) {
		q.push(i);
	}
	assert(!q.isEmpty());
	for (int i = 0; i < 15; ++i) {
		assert(q.front() == i);
		assert(q.pop() == i);
	}
	for (int i = 0; i < 5; ++i) {
		q.push(i);
	}
	for (int i = 0; i < 5; ++i) {
		assert(q.front() == i);
		assert(q.pop() == i);
	}
	try {
		q.pop();
		assert(false);
	} catch (...) {
		assert(true);
	}
	try {
		q.front();
		assert(false);
	} catch (...) {
		assert(true);
	}
}

void smallTestPQ() {
	PriorityQueue<int, int> PQ;
	assert(PQ.isEmpty());
	for (int i = 10; i >= 0; --i) {
		PQ.push(i, i);
	}
	assert(!PQ.isEmpty());
	int a, b;
	for (int i = 0; i <= 10; ++i) {
		PQ.top(a, b);
		assert(a == i && b == i);
		PQ.pop(a, b);
		assert(a == i && b == i);
	}
	try {
		PQ.top(a, b);
		assert(false);
	} catch (...) {
		assert(true);
	}
	try {
		PQ.pop(a, b);
		assert(false);
	} catch (...) {
		assert(true);
	}
	PQ.push(11, 11);
	PQ.push(12, 12);
	PQ.push(13, 13);
	PQ.push(15, 15);
	PQ.push(14, 14);
}