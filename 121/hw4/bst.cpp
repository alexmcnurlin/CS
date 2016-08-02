// Alex McNurlin
// File: bst.cpp
// Created: 4/18/16

#include "bst.h"
#include <iostream>
using namespace std;


void Bst::add_node( Movie *node ) {
	if ( root == NULL ) {					// Empty case
		root = new Leaf();
		root->value = node;
		return;
	}

	Leaf *p = root;

	while ( 1 ) {									// Traverse the tree and insert node
		if ( node->get_title() <= p->value->get_title() ) {  // Check left side

			if ( p->left == NULL ) {	// Node insertion 
				p->left = new Leaf();
				p->left->value = node;
				return;
			} else 
				p = p->left;

		} else if ( node->get_title() > p->value->get_title() ) {// Check right side

			if ( p->right == NULL ) {	// Node insertion
				p->right = new Leaf();
				p->right->value = node;
				return;
			} else 
				p = p->right;

		}

	}
}


void Bst::print_actors( string title ) {
	if ( root == NULL ) {					// Empty case
		cout << "Title \"" << title << "\" not found" << endl;
		return;
	}

	Leaf *p = root;

	while ( 1 ) {									              // Traverse the tree and find title
		if ( title <= p->value->get_title() ) {		// Check left branch

			if ( p->value->get_title() == title ) {	// Check if the title matches
				p->value->print_actors();							// Print results
				return;

			} else if ( p->left == NULL ) {			   	// If the title doesn't match and 
																							// there's nowhere left to check
				cout << "Title \"" << title << "\" not found" << endl;
				return;
			} else {																// Check next interation
				p = p->left;

			}

		} else if ( title > p->value->get_title() ) {// right branch

		  if ( p->right == NULL ) {	 	         		// If the title doesn't match and 
																							// there's nowhere left to check
				cout << "Title \"" << title << "\" not found" << endl;
				return;
			} else {																// Check next interation
				p = p->right;

			}

		}

	}
}


// Prints all shows of a given actor
// The first function is called first, which calls the second recursively
void Bst::print_shows_by_actor( string actor ) {
	Leaf *p = root;

	// Checks the left branch
	cout << "Shows/Movies with actor \"" << actor << "\": " << endl;
	if ( p->left != NULL ) {
		print_shows_by_actor( *p->left, actor );
	} 

	// Only prints if the actor is in the show/movie
	if ( p->value->has_actor( actor ) ) {
		cout << '\t' << p->value->get_title() << endl;
	}

	// Checks the left branch
	if ( p->right != NULL ) {
		print_shows_by_actor( *p->right, actor );
	} 
}
void Bst::print_shows_by_actor( Leaf &node, string actor ) {
	Leaf *p = new Leaf();
	p = &node;

	// Checks the left branch
	if ( p->left != NULL ) {
		print_shows_by_actor( *p->left, actor );
	} 

	// Only prints if the actor is in the show/movie
	if ( p->value->has_actor( actor ) ) {
		cout << '\t' << p->value->get_title() << endl;
	}

	// Checks the right branch
	if ( p->right != NULL ) {
		print_shows_by_actor( *p->right, actor );
	} 
}


void Bst::print_shows_of_decade( int year ) {
	Leaf *p = root;

	cout << "Shows/Movies starting in  \"" << year << "-" << year+10 << "\": " << endl;
	// Recursively check left branch
	if ( p->left != NULL ) {
		print_shows_of_decade( *p->left, year );
	} 

	// Only print show if it's in the given decade
	if ( p->value->started_in_decade( year ) ) {
		cout << '\t' << p->value->get_title() << endl;
	}

	// Recursively check right branch
	if ( p->right != NULL ) {
		print_shows_of_decade( *p->right, year );
	} 
}
void Bst::print_shows_of_decade( Leaf &node, int year ) {
	Leaf *p = new Leaf();
	p = &node;

	// Recursively check left branch
	if ( p->left != NULL ) {
		print_shows_of_decade( *p->left, year );
	} 

	// Only print show if it's in the given decade
	if ( p->value->started_in_decade( year ) ) {
		cout << '\t' << p->value->get_title() << endl;
	}

	if ( p->right != NULL ) {
		print_shows_of_decade( *p->right, year );
	} 
}


// The first function is called first, which calls the second recursively
void Bst::print_tree() {
	Leaf *p = root;

	cout << "Shows/Movies in the database: " << endl;

	if ( p->left != NULL ) {
		print_tree( *p->left );
	} 

	cout << '\t' << p->value->get_title() << endl;

	if ( p->right != NULL ) {
		print_tree( *p->right );
	} 
}
void Bst::print_tree( Leaf &node ) {
	Leaf *p = new Leaf();
	p = &node;

	if ( p->left != NULL ) {
		print_tree( *p->left );
	} 

	cout << '\t' << p->value->get_title() << endl;

	if ( p->right != NULL ) {
		print_tree( *p->right );
	} 
}
