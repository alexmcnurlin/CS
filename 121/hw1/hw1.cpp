/*
 * Alex McNurlin
 * CS121
 * Homework 1
 * Bruce Boldon
 * 2/12/16
 * 
 * Time Log
 *    * 2/10 - 18:00-
 */

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;


void open_file( ifstream &opened_file, const std::string &file_to_read );     // Opens file for input
void open_file( ofstream &opened_file, const std::string &file_to_read );     // Opens file for output
void read_file_size( ifstream& file, int& x, int& y );                        // Reads the size of array to be used
void read_file( ifstream& file, int **the_array, int x, int y );              // Read the contents of the file
char* int_to_bin( int n );                                                    // Converts int to binary string


int main() {
  string file_to_read;  // The file to read from
  string file_to_write; // The file to be written to
  ifstream opened_file; // The file to be read from
  ofstream write_file;  // The file to be written to
  int x_size, y_size;   // The number of rows and columns to be read into the program


  cout << "Please enter file to read from: ";             // Prompts user for file input
  cin >> file_to_read;
  cout << "Please enter file to write to: ";
  cin >> file_to_write;
  open_file( opened_file, file_to_read );
  open_file( write_file, file_to_write );
  

  read_file_size( opened_file, x_size, y_size );                // Reads the size of array into x_size and y_size
  int* pixel_array[x_size*y_size];                              // I ran into too many probrems using a 2d array, so it's a single dimensional array instead

  read_file( opened_file, pixel_array, x_size, y_size );        // Reads the rest of the data into the function

  for ( int i = 0; i < x_size; i++ ) {                          // Loops through the data and converts it to binary
    for ( int j = 0; j < y_size; j++ ) {
      char* temp = int_to_bin( *pixel_array[ i*y_size + j ] );
      write_file << temp;                                       // Writes data to file
    }
    write_file << endl;
  }


  return 0;
}


void read_file_size( ifstream& file, int &x, int &y ) {
  file >> x >> y;
}


void read_file( ifstream& file, int **the_array,  int x, int y ) {
  int temp;
  for ( int i = 0; i < x; i++ ) {
    for ( int j = 0; j < y; j++ ) {
      file >> hex >> temp;                    // Thanks to stackoverflow.com/questions/5040681/how-to-read-hex-values-from-a-file-using-fstream-in-c for reading as hex
      the_array[i*y + j] = new int(temp);
       
    }
  }
}


void open_file( ifstream &opened_file, const std::string &file_to_read ){     // Opens file for input
  opened_file.open( file_to_read.c_str() );           // Opens file 

  if ( opened_file.fail() ) {               // Exits if file fails to open
    cout << "Could not open file " << file_to_read << endl;
    cout << "Exiting...";
    exit(1);
  }
}


void open_file( ofstream &opened_file, const std::string &file_to_read ){     // Opens file for output
  opened_file.open( file_to_read.c_str() );           // Opens file

  if ( opened_file.fail() ) {               // Exits if file fails to open
    cout << "Could not open file " << file_to_read << endl;
    cout << "Exiting...";
    exit(1);
  }
}


char* int_to_bin( int n ) {                                                   // Converts int to binary string
  int i = 4;
  char* temp = new char[i];
  do {
    i--;
    temp[i] = ( n % 2 ) + '0';
    n /= 2;
  } while ( i > 0 );
  return temp;
}
