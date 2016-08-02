// Alex McNurlin
// File: hw3.cpp
// CS121
// Programming assignment 3
// 3/7/16

#include "queue.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;


int Parse_char( char** maze, int x, int y, int x_size, int y_size, Queue &the_queue );


int main() {

  char filename[256]; // 255 is the max length of of a filename in ext4 and fat32

  // gets the file to read from
  cout << "Enter file to read: ";
  cin >> filename;

  // Open file + error checking
  ifstream infile;
  infile.open(filename);  
  if (infile.fail()) {
    cout << "Invalid file " << filename << endl << "Exiting..." << endl;
    exit(1);
  }

  // Declace Queue, read in maze size.
  Queue coordinates;
  int x_size, y_size;
  infile >> x_size >> y_size;

  // Creating dynamically allocated array
  char** maze = new char*[x_size];   // Creates the first dimension of array
  for ( int i=0; i<x_size; i++ ) {   // Creates second dimension of array
    maze[i] = new char[y_size];
    for ( int j=0; j<y_size; j++ ) { // Initialize array by reading infile
      infile >> maze[i][j];
      if ( maze[i][j] == 'S' ) {     // Checks if a point is the starting point
        int point[2] = {i,j};
        coordinates.Enqueue( point );// Enqueues the starting point
      }
    }
  }

  // Now to actually solve the maze
  while (1) {
    // Checks if the queue is empty, which only happens when the maze
    // cannot be solved
    if ( !coordinates.Size() ) {

      // Prints out the solved maze for good measure
      for ( int i=0; i<x_size; i++ ) {
        for ( int j=0; j<x_size; j++ ) {
          cout << maze[i][j];
        }
        cout << endl;
      }

      cout << "Maze cannot be solved!" << endl;

      exit(0);
    }

    // Dequeues the next point in the list
    int *point;
    point = coordinates.Dequeue();
    int x = point[0];
    int y = point[1];


    // Checks the points in all 4 directions.
    Parse_char( maze, x-1, y, x_size, y_size, coordinates) ;
    Parse_char( maze, x, y-1, x_size, y_size, coordinates) ;
    Parse_char( maze, x+1, y, x_size, y_size, coordinates) ;
    Parse_char( maze, x, y+1, x_size, y_size, coordinates) ;
  }
  

  infile.close();
} // End main()



int Parse_char( char** maze, int x, int y, int x_size, int y_size, Queue &the_queue ) {

  // Checks if the points are within the bounds of the maze
  if ( !( x<0 || x>=x_size || y<0 || y>=y_size ) ) {

    switch ( maze[x][y] ) {

      // If there's a path, mark the point as visited, and queue the point
      case '.':
        int temp[2];
        temp[0] = x;
        temp[1] = y;
        maze[x][y] = 'v';
        the_queue.Enqueue( temp );
        break;

      // If the point is the goal, exit with success
      case 'G':

        // Prints out the solved maze for good measure
        for ( int i=0; i<x_size; i++ ) {
          for ( int j=0; j<x_size; j++ ) {
            cout << maze[i][j];
          }
          cout << endl;
        }

        cout << "The end is located at (" << x << ", " << y << ")" << endl;
        exit(0);

    }
  }
}
