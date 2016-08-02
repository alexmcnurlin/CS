// Alex McNurlin
// File: hw4.cpp
// Created: 4/18/16

#include <iostream>
#include <fstream>
#include "bst.h"
#include <cstdlib>
#include <string.h>
using namespace std;


int main() {
  // Open file
  // This is hardcoded just to make testing easier
  char filename[32] = "tvDB.txt";
  //cout << "Enter filename: ";
  //cin >> filename;
  ifstream in_file(filename);
  if ( in_file.fail() ) {
    cout << "File " << filename << " is invalid " << endl << "Exiting..." << endl;
    exit(1);
  }

  Bst    movie_tree;
  string movie_title;
  string start_year;
  string end_year;
  string category;
  string url;
  string actor;
  // Reads in contents from file movie by movie
  // An instance of the Movie class is created and each instance is added
  // to the Binary Search Tree
  while( !in_file.eof() ) {
    Movie *new_movie = new Movie();

    // Read in title (Everything until '(' )
    getline( in_file, movie_title, '(' );
    new_movie->add_title( movie_title.erase( movie_title.size()-1, 1 ) );
    //                                ^ This erases the last character, which
    //                                  is always a space.

    // Read in starting year (from '(' until '-' )
    getline( in_file, start_year, '-' );            //
    new_movie->add_start_year( stoi(start_year) );

    // Read in end year (From '-' until '(' )
    getline( in_file, end_year, ')' );
    new_movie->add_end_year( stoi(end_year) );

    getline( in_file, actor );  // There is always an extra space after the ')'
                                // This gets rid of that

    // Read in category
    getline( in_file, category );
    new_movie->add_category( category );

    // Read in url
    getline( in_file, url );
    new_movie->add_url( url );

    // Read in remaining lines until empty line as actors
    while( 1 ) {
      actor = "";
      getline( in_file, actor );
      new_movie->add_actor( actor );

      if ( actor == "" ) {
        break;
      }
    }


    // Add the movie to the tree
    movie_tree.add_node( new_movie );


  }

  // Print out the necessary information
  movie_tree.print_tree();
  cout << endl;
  movie_tree.print_actors("The Saint");
  movie_tree.print_actors("Benson");
  movie_tree.print_actors("Dexter's Laboratory");
  movie_tree.print_actors("Futurama");
  movie_tree.print_actors("Star Trek");
  cout << endl;
  movie_tree.print_shows_by_actor("Nancy Cartwright");
  movie_tree.print_shows_by_actor("Marcia Wallace");
  movie_tree.print_shows_by_actor("Bill Daily");
  movie_tree.print_shows_by_actor("Joe Penny");
  movie_tree.print_shows_by_actor("Michael Jeter");
  movie_tree.print_shows_by_actor("Madeleine Sherwood");
  cout << endl;
  movie_tree.print_shows_of_decade( 1975 );
  movie_tree.print_shows_of_decade( 2000 );

  return 0;
}
