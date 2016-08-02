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

    void AddNode(double n);
    double DeleteHead();
    double GetTop();
    std::string ListNodes();
    int  Size();
  private:
    struct node {
      node *next; 
      double value; 
    };

    node *head; // Points to the head of the list.
};

#endif
