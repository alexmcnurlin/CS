// Alex McNurlin
// File: ll.cpp
// Date: 2/25/16

#include "ll.h"
// NULL isn't a builtin in my environment. This adds that functionality.
#include <cstddef>
#include <iostream>
#include <string>
// Allows for some convenient double to string conversion.
#include <sstream>

Ll::Ll() {
  head = NULL;
}

Ll::~Ll() {
  node *p = head;
  node *q = p;
  head = head->next;
  while (q != NULL) {
    p = q;
    q = p->next;
    delete p;
  }
}


// Adding a single node to the head of the list.
void Ll::AddNode(double n) {
  node *p;
  p = new node();
  p->value = n;
  p->next = head;
  head = p;
}


// Deletes the top node of the list. Does nothing if empty.
double Ll::DeleteHead() {
  if (head != NULL) {
    double return_value = head->value;
    node *p;
    p = head;
    head = head->next;
    delete p;
    return return_value;
  }
}


// Simply gets the value of the top node. Should return 0 if empty.
double Ll::GetTop() {
  return head->value;
}


// Returns a list of all of the nodes as a string. 
std::string Ll::ListNodes() {
  node *p;
  p = head;
  // This is a very convenient way to convert a double to a string.
  std::ostringstream strs;
  while (p != NULL) {
    // Simply pushes each value into the stringstream.
    strs << p->value << " ";
    p = p->next;
  }
  std::string str = strs.str();
  return str;
}


// Returns the size of the list. 0 if empty.
int  Ll::Size() {
  int i = 0;
  node *p;
  p = head;
  while (p != NULL) {
    i += 1;
    p = p->next;
  }

  return i;
}
