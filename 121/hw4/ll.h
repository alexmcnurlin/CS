// Alex McNurlin
// File: ll.h
// Created: 2/25/16
// Edited: 4/15/16
//        - Edited to use strings for hw4

#ifndef LL_H
#define LL_H

#include <string>
using namespace std;

// A class implementation of a linked list.
class Ll {
  public:
    Ll();
    ~Ll();

    void     add_node( string n );
    string   delete_head();
    string   get_top();
    int      size();
    void     print_nodes();
    bool     has_node( string test_node );

  private:
    struct node {
      node   *next; 
      string  value; 
    };

    node *head; // Points to the head of the list.
};

#endif
