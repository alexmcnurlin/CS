// Alex McNurlin
// File: queue.cpp
// Date: 3/7/16
using namespace std;

#include "queue.h"


// Add a point to the beginning of the list
void Queue::Enqueue( int point[2] ) {
  list.AddNode(point);
}

// Delete from the end of the list
int* Queue::Dequeue() {
  return list.DeleteTail();
}

// Get the size
int Queue::Size() {
  return list.Size();
}
