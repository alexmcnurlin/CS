// Alex McNurlin
// File: stack.cpp
// Date: 2/25/16

#include "stack.h"
#include <iostream>
#include <string>

// Pushes the double to the top of the stack. 
double Stack::Push( double n ) {
  LinkedList.AddNode(n);
}


// Removes and returns the top value
double Stack::Pop() {
  return LinkedList.DeleteHead();
}


// Returns the value of the topmost item in the stack.
double Stack::Top() {
  return LinkedList.GetTop();
}


// Prints out a list of the items in the stack.
std::string Stack::PrintStack() {
  return LinkedList.ListNodes();
}


bool Stack::IsEmpty() {
  return !LinkedList.Size();
}
