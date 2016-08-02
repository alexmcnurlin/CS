// Alex McNurlin
// File: queue.h
// Date: 3/7/16
#include "ll.h"

#ifndef QUEUE_H
#define QUEUE_H

// A simple Queue implementation, that acts as a wrapper for Ll.h
class Queue {
	public:
		Queue() {};
		~Queue() {};

		void Enqueue( int point[2]  );
		int* Dequeue();
		int Size();

	private:
		Ll list;
};

#endif
