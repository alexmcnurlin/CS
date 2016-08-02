// Alex McNurlin
// File: ll.cpp
// Date: 2/25/16

#include "ll.h"
#include <iostream>
using namespace std;

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
void Ll::AddNode(int n[]) {
  node *p;
  p = new node();
  p->value[0] = n[0];
  p->value[1] = n[1];
  p->next = head;
  head = p;
}


int* Ll::DeleteTail() {
  if (head->next == NULL) {
      static int return_value[2];
      return_value[0] = head->value[0];
      return_value[1] = head->value[1];
      delete head;
      head = NULL;
      return return_value;
  } else if ( head == NULL ) {
    static int return_value[2];
    return_value[0] = 1000;
    return_value[1] = 1000;
    return return_value;
  } else {
      node  *q, *p;
      q = head;
      p = head->next;
      while (p->next != NULL) {
          q = p;
          p = p->next;
      }
      static int return_value[2];
      return_value[0] = p->value[0];
      return_value[1] = p->value[1];
      delete p;
      q->next = NULL;
      return return_value;
  }
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
