// Alex McNurlin
// File: movie.cpp
// Created: 4/18/16

#include "movie.h"
#include <string.h>
#include <iostream>

void Movie::add_title( string new_title ) {
  title = new_title;
}


void Movie::add_start_year( int year ) {
  start_year = year;
}


void Movie::add_end_year( int year ) {
  end_year = year;
}


void Movie::add_category( string new_category ) {
  category = new_category;
}


void Movie::add_url( string new_url ) {
  url = new_url;
}


void Movie::add_actor( string actor ) {
  actors.add_node(actor);
}


bool Movie::has_actor( string actor ) {
  return actors.has_node( actor );
}


bool Movie::started_in_decade( int year ) {
  return ( start_year <= year+10 && start_year >= year );
}


void Movie::print_actors() {
  cout << "Actors in \"" << title << "\":";
  actors.print_nodes();
}

string Movie::get_title() {
  return title;
}
