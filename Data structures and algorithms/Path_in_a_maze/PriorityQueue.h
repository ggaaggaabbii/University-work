#pragma once

#include <bits/stdc++.h>

template<typename P>
bool defaultCompare(P a, P b)
{
	return a < b;
}

template <typename T, typename P>
struct PQNode
{
	T info;
	P priority;
	PQNode* next;
	PQNode* prev;
};

template <typename T, typename P>
class PriorityQueue
{
private:
	PQNode<T, P>* head;
	PQNode<T, P>* tail;
	bool (*cmpFunction)(P, P);

public:
	PriorityQueue(bool (*cmp)(P, P) = &defaultCompare<P>): cmpFunction{cmp} {
		head = nullptr;
		tail = nullptr;
	}
	~PriorityQueue() {
		while (head != nullptr) {
			tail = head->next;
			delete head;
			head = tail;
		}
	}
	void push(T e, P p) {
		PQNode<T, P>* newNode = new PQNode<T, P>;
		newNode->info = e;
		newNode->priority = p;
		newNode->next = nullptr;
		int count = 0;

		if (head == nullptr) {
			newNode->prev = nullptr;
			head = newNode;
			tail = head;
			return;
		}
		PQNode<T, P> *aux = head;
		while (aux != nullptr && cmpFunction(aux->priority, p)) {
			aux = aux->next;
			count ++;
		}
		if (aux == nullptr) {
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		} else {
			newNode->prev = aux->prev;
			newNode->next = aux;
			if (aux->prev != nullptr) {
				aux->prev->next = newNode;
			} else {
				head = newNode;
			}
			aux->prev = newNode;
		}
	}
	void pop(T &e, P &p) {
		if (head == nullptr) {
			throw std::string{"Empty queue"};
		}
		e = head->info;
		p = head->priority;
		PQNode<T, P> *aux = head;
		head = head->next;
		if (head == nullptr) {
			tail = head;
		} else {
			head->prev = nullptr;
		}
		delete aux;
	}
	void top(T &e, P &p) {
		if (head == nullptr) {
			throw std::string{"Empty queue"};
		}
		e = head->info;
		p = head->priority;
	}
	bool isEmpty() {
		return head == nullptr;
	}
};