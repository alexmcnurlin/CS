#include <iostream>
#include <cstdlib>
#include <fstream>
#include "hash.h"

using namespace std;

int main() {
  char filename[32];
  cout << "Enter filename: ";
  cin >> filename;
  ifstream in_file(filename);
  if ( in_file.fail() ) {
    cout << "File " << filename << " is invalid " << endl << "Exiting..." << endl;
    exit(1);
  }

  // Read in lines until end of file
  while ( !in_file.eof() ) {
    char in_char_string[32];

    in_file.getline( in_char_string, 32 );

    Insert( in_char_string ); // Insert line into hash table
  }

  // Count the number of values in each bucket
  CountHashTable();
  cout << endl;

  // find buckets with minimum and maximum values
  HashMinMax();
  cout << endl;

  // Lookup 10 words in the table
  char words_to_lookup[10][32] = {
    "unity", 
    "za", 
    "abler", 
    "wager", 
    "wormy", 
    "memorable",
    "mango",
    "physics",
    "nameless",
    "cubit"
  };

  for (int i = 0; i < 10; i++ ) {
    Lookup_with_output( words_to_lookup[i] );
  }
  cout << endl;

}
