// Data Structures and Algorithms 1
// Professor Sable
// Ivan Chowdhury
// Spring 2018


#ifndef __SL_HPP
#define __SL_HPP

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class SimpleList {
	
public:
    //Listname and structure initializing 
	SimpleList(string name);
	virtual void push(T val) = 0;
	virtual T pop() = 0;
	virtual int getSize() = 0;
	string listName;

private:
	//private nested class node;
	class Node {
	public:
		Node(T val, Node * ptr) {
			this->data = val;
			this->next = ptr;
		}
		T data;
		Node * next;
	};
	Node * start;
	Node * end;
};

protected:
	void insert_end(T val);
	void insert_start(T val);
	T   remove_front();
    // 3 functions, set to insert a node at the start and end of the list, and remove a node at the start of the list. Constant time;
	int size;
	
// Derived classes for stack and queue. Push, pop,and getSize functions for stack and queue;
template <typename T>
class Stack : public SimpleList<T> {
public:
	Stack(string name);
	void push(T val);
	T pop();
	int getSize();
};

template <typename T>
class Queue : public SimpleList<T> {
public:
	Queue(string name);
	void push(T val);
	T pop();
	int getSize();
};



/*SimpleList constructor. Initializes start and end nodes of linked list to null, and size to 0 (empty list);*/
template <typename T>
SimpleList<T>::SimpleList(string name) {
	this->listName = name;
	this->start = nullptr;
	this->end = nullptr;
	this->size = 0;

}


//Insert node at end of SimpleList, for queues);
template <typename T>
void SimpleList<T>::insert_end(T val) {
	Node* newNode = new Node(val, nullptr);
    //Ensure that, if the list is empty, both the Start and End nodes are set to the new node. otherwise just the End node;
	if (this->size == 0) {
		this->end = newNode;
		this->start = newNode;
	}
	else {
		this->end->next = newNode;
	}
}

//Insert node at start of SimpleList for stacks);
template <typename T>
void SimpleList<T>::insert_start(T val) {
	/*Create new node, made start point to it*/
	Node* newNode = new Node(val, this->start);
	this->start = newNode;
}

//Removes node from start of SimpleList, for both stack and queue;
template <typename T>
T   SimpleList<T>::remove_front() {
	Node * newNode = this->start;
	this->start = newNode->next;
	T data = newNode->data;
	delete newNode;
	return data;
}

//Stack constructer;
template <typename T>
Stack<T>::Stack(string name) : SimpleList<T>(name) {
}

//Stack Push: node insertion at start + increment size value;
template <typename T>
void Stack<T>::push(T val) {
	this->insert_start(val);
	this->size++;
}

//Stack Pop: node removal from start + decrement size;
template <typename T>
T Stack<T>::pop() {
	this->size--;
	return this->remove_front();
}

//return stack size;
template <typename T>
int Stack<T>::getSize() {
	return this->size;
}

//Queue constructer;
template <typename T>
Queue<T>::Queue(string name) : SimpleList<T>(name) {
}

//Queue push : node insertion at end + increment size;
template <typename T>
void Queue<T>::push(T val) {
	this->insert_end(val);
	this->size++;
}

//Queue Pop: remove from the start and decrement the size;
template <typename T>
T Queue<T>::pop() {
	this->size--;
	return this->remove_front();
}

//return queue size
template <typename T>
int Queue<T>::getSize() {
	return this->size;
}

#endif