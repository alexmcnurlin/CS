// Alex McNurlin
// File: stack.h
// Date: 2/25/16

#ifndef STACK_H
#define STACK_H

#include "ll.h"

// A stack implementation of a linked list. 
// This class is a wrapper around ll.h
class Stack {
	public:
		Stack() {};
		~Stack() {};

		double Push( double n );
		double Pop();
		double Top();
		std::string   PrintStack();
		bool   IsEmpty();

	private:
		Ll LinkedList;
};

#endif
