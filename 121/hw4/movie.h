// Alex McNurlin
// File: movie.h
// Created: 4/18/16

#include "ll.h"
#include <string>
#ifndef MOVIE_H
#define MOVIE_H


class Movie {
  public:
    Movie() {};

    void add_title(         string title    );
    void add_start_year(    int    year     );
    void add_end_year(      int    year     );
    void add_category(      string category );
    void add_url(           string url      );
    void add_actor(         string actor    );

    bool has_actor(         string actor    );
    bool started_in_decade( int    year     );
    void print_actors();
    string get_title();
    
  private:
    string title;
    int  start_year;
    int  end_year;
    string category;
    string url;
    Ll actors;
};

#endif
