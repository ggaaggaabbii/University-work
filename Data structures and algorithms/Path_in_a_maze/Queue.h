#pragma once

#include <bits/stdc++.h>

template <typename T>
struct QNode
{
	int next;
	int prev;
	T info;
};

template<typename T>
class Queue
{
private:
	QNode<T>* elems;
	int cap;
	int head;
	int tail;
	int firstEmpty;
	void resize() {
		QNode<T> *newElems = new QNode<T>[2 * cap];
		for (int i = 0; i < cap; ++i) {
			newElems[i] = elems[i];
		}

		cap *= 2;
		for (int i = cap / 2; i < cap; ++i) {
			newElems[i].next = i + 1;
			newElems[i].prev = i - 1;
		}
		newElems[cap - 1].next = -1;
		delete[] elems;
		elems = newElems;
		firstEmpty = cap / 2;
	}


public:
	Queue() {
		cap = 10;
		head = -1;
		tail = -1;
		firstEmpty = 0;
		elems = new QNode<T>[10];
		for (int i = 0; i < 10; ++i) {
			elems[i].next = i + 1;
			elems[i].prev = i - 1;
		}
		elems[9].next = -1;
	}

	~Queue() {
		delete[] elems;
	}


	void push(T e) {
		if (firstEmpty == -1) {
			resize();
		}
		int aux = firstEmpty;
		firstEmpty = elems[firstEmpty].next;
		elems[aux].info = e;
		if (head == -1) {
			head = aux;
			tail = aux;
			elems[aux].next = -1;
			elems[aux].prev = -1;
		} else {
			elems[aux].next = head;
			elems[head].prev = aux;
			elems[aux].prev = -1;
			head = aux;
		}
	}

	T pop() {
		if (head == -1) {
			throw std::string{"Empty queue"};
		}
		if (head == tail) {
			head = -1;
		}
		int newTail = elems[tail].prev;
		elems[newTail].next = -1;
		elems[tail].next = firstEmpty;
		elems[tail].prev = -1;
		firstEmpty = tail;
		tail = newTail;
		return elems[firstEmpty].info;
	}

	T front() {
		if (tail == -1) {
			throw std::string{"Empty queue"};
		}
		return elems[tail].info;
	}

	bool isEmpty() {
		return tail == -1;
	}

};