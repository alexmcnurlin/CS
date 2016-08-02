// Alex McNurlin
// File: ll.cpp
// Created: 2/25/16
// Edited: 4/15/16
//        - Edited to use strings for hw4

#include "ll.h"
// NULL isn't a builtin in my environment. This adds that functionality.
#include <cstddef>
#include <iostream>
#include <string>
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
void Ll::add_node( string n ) {
  node *p;
  p = new node();
  p->value = n;
  p->next = head;
  head = p;
}


// Deletes the top node of the list. Does nothing if empty.
string Ll::delete_head() {
  if ( head != NULL ) {
    string return_value = head->value;
    node *p;
    p = head;
    head = head->next;
    delete p;
    return return_value;
  }
}


// Simply gets the value of the top node. Should return 0 if empty.
string Ll::get_top() {
  return head->value;
}


// Returns the size of the list. 0 if empty.
int  Ll::size() {
  int i = 0;
  node *p;
  p = head;
  while (p != NULL) {
    i += 1;
    p = p->next;
  }

  return i;
}

// Returns an array of the contents (type string)
void Ll::print_nodes() {
  node *p = new node();

  if ( head == NULL ) { // Do nothing
  } else {
    p = head;
    cout << p->value << endl;

    while ( p->next != NULL ) {
      p = p->next;
      cout << '\t' << p->value << endl;
    }

  }
}

bool Ll::has_node( string test_node ) {
  node *p = new node();

  if ( head == NULL ) { // Do nothing
    return false;
  } else {
    p = head;
    if ( p->value == test_node ) {    // Test if the test_node is at the head of list
      return true;
    }

    while ( p->next != NULL ) {   // Traverse the list 
      p = p->next;
      if ( p->value == test_node ) {  // Test if the test_node is in the list
        return true;
      }
    }
    return false;                 // Return false if no matches are found

  }
}
