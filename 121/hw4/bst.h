// Alex McNurlin
// File: bst.h
// Created: 4/18/16

#include "movie.h"
#include <iostream>
#ifndef BST_H
#define BST_H

class Bst {
  public:
    typedef struct leaf {
      Movie *value;
      leaf  *right = NULL;
      leaf  *left  = NULL;
    } Leaf;

    Bst() {
      root = NULL;
    }

    void add_node( Movie *node );
    void print_actors( string title );

    void print_tree();
    void print_tree( Leaf &node );

    void print_shows_by_actor( string actor );
    void print_shows_by_actor( Leaf &node, string actor );

    void print_shows_of_decade( int year );
    void print_shows_of_decade( Leaf &node, int year );


  private:
    Leaf *root;
};

#endif
