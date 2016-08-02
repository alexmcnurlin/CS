// Alex McNurlin
// File: ll.h
// Date: 2/25/16

#ifndef LL_H
#define LL_H

#include <string>

// A class implementation of a linked list.
class Ll {
  public:
    Ll();
    ~Ll();

    void AddNode(int n[]);
    int* DeleteTail();
    int  Size();

  private:
    struct node {
      node *next; 
      int value[2]; 
    };

    node *head; // Points to the head of the list.
};

#endif
