#pragma once

#include <iostream>
#include <fstream>
#include "Iterator.h"
using namespace std;

template <class T>
class List {

	struct ListNode {
		T data;
		ListNode * next;

		ListNode(const ListNode& listNode) {
			data =listNode.data;
		}

		ListNode() {
			next = NULL;
		}

		ListNode(const T& dat) {
			data = dat;
		}
		void Print() {
			cout << data;
		}
	};

public:
	typedef ListNode node_type;
	typedef _iterator<node_type> iterator;
	//constructors / destructors
	List();
	~List();

	//methods
	iterator begin();//Returns an iterator addressing the first element 
	iterator end();//Returns an iterator that addresses the location 
   //succeeding the last element


	void clear();//Erases all the elements of a list.
	bool empty();//Tests if a list is empty.
	void load(const char *filename);

	iterator find(const node_type & val);//Returns an iterator to the 
// first element in a list that 
//match a specified value.

	void pop_front();//Deletes the element at the beginning of a list.

	void push_front(node_type val);//Adds an element to the beginning 
  //of a list.
	void remove(const node_type val);//Erases first element in a list that 
   //match a specified value.

	int size();//Returns the number of elements in a list.

	void splice(iterator _Where, List<T>& _Right);//Removes element from //the target list and inserts it in first
// position of the argument list.
	void	Print();//Dumps list into the screen
	node_type parseFrom(char *str);
private:

	iterator findBefore(const node_type & val);
	void correctIterators();

	node_type *head;
	iterator *first, *last;
	int length;
};

template <typename T>
List<T>::~List() {
	delete head;
	delete first;
	delete last;
}

template <typename T>
List<T>::List() {
	head = NULL;
	first = NULL;
	last = NULL;
	length = 0;
}

template <typename T>
typename List<T>::iterator List<T>::begin() {
	if (first == NULL) return NULL;
	return *first;
}

template <typename T>
typename List<T>::iterator List<T>::end() {
	return *last;
}

template <typename T>
typename List<T>::iterator List<T>::find(const node_type &val) {
	node_type *p = head;

	while (p != NULL && p->data != val.data) {
		p = p->next;
	}
	
	return p;
}

template <typename T>
typename List<T>::iterator List<T>::findBefore(const node_type &val) {
	node_type *p = head;
	node_type *before = p;

	while (p != NULL && p->data != val.data) {
		before = p;
		p = p->next;
	}

	return before;
}

template <typename T>
void List<T>::remove(const node_type val) {
	iterator it = find(val);
	iterator itBefore = findBefore(val);

	node_type *p = &(*it);
	node_type *p_before = &(*itBefore);

	if (it == NULL) {
		cout << "It = NULL in remove" << endl;
	}
	//Start of the list
	if (it == itBefore) {
		head = p->next;
		delete p;
		p = NULL;

		correctIterators();
		return;
	}
	
	p_before->next = p->next;
	delete p;
	p = NULL;

	length--;
	correctIterators();
}

template <typename T>
void List<T>::push_front(node_type val) {
	node_type *p = new node_type(val.data);

	if (head == NULL) {
		head = p;
		length = 1;
		head->next = NULL;
	} else {
		node_type *buffer = head;
		head = p;
		head->next = buffer;
		length++;
	}
	correctIterators();
}

template <typename T>
void List<T>::pop_front() {
	if (head != NULL) {
		remove(head->data);
	} else {
		cout << "Head is NULL, func pop_front" << endl;
	}
}

template <typename T>
void List<T>::Print() {
	List<T>::node_type *p = head;

	while (p != NULL) {
		p->Print();
		p = p->next;
	}
}

template <typename T>
void List<T>::clear() {
	while (head != NULL) {
		pop_front();
	}
}

template <typename T>
bool List<T>::empty() {
	return length == 0;
}

template <typename T>
int List<T>::size() {
	return length;
}

template <typename T>
void List<T>::splice(iterator _Where, List<T>& _Right) {
	if (_Where == NULL) {
		exit(1);
	}
	
	node_type value = (*_Where).data;
	this->remove((*_Where).data);
	_Right.push_front(value);
}

template <typename T>
void List<T>::correctIterators() {
	delete first;
	delete last;

	first = new iterator(head);

	node_type *p = head;

	while (p != NULL) {
		p = p->next;
	}

	last = new iterator(p);
}

template <class T>
typename List<T>::node_type List<T>::parseFrom(char *str) {
	T element;
	element.parseFrom(str);
	return element;
}

template <typename T>
void List<T>::load(const char* filename) {
	ifstream fcin;
	fcin.open(filename);

	char string[50];

	while (!fcin.eof()) {
		fcin >> string;
		push_front(parseFrom(string));
	}
}