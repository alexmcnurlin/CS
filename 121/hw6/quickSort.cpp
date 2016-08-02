/*  quickSort.cpp
 *
 *  Bruce M. Bolden
 *  November 18, 1998
 *
 *  Edited by Alex McNurlin
 *  May 5, 2016
 *    All lines edited are commented with 4 slashes (////)
 *    and a comment on what was changed
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

typedef int aType;


    //  prototypes
void Quicksort( aType a[], int first, int last );
int Pivot( aType a[], int first, int last );

void  Swap( aType &v1, aType &v2 );
void  PrintArray( aType A[], int nElements );

int c = 0; ////  c is the number of comparisons, s is the number of swaps
int s = 0; //// Added these lines

int main()
{
  //// Begin edited code
  char filename[32];

  cout << "Enter filename: ";
  cin >> filename;
  ifstream in_file(filename);
  if ( in_file.fail() ) {
    cout << "File " << filename << " is invalid " 
      << endl << "Exiting..." << endl;
    exit(1);
  }

  // Read in lines until end of file
  char in_char[32];
  int in_int = -1;

  // The size of array_to_sort will always be 10000, 
  // but the size will be recorded in size. Also 
  int array_to_sort[10001];
  int size = 0;

  do {
    size++;
    in_file.getline( in_char, 32 );
    in_int = atoi(in_char);

    //cout << in_int << " " << size-1 << endl;

    array_to_sort[size-1] = in_int;
  } while ( !in_file.eof() );
  // for some reason, the program always reads in one more line thats empty. 
  // This fixes that
  size--;

  cout << "Sorting..." << endl;
  Quicksort( array_to_sort, 0, size-1 );

  PrintArray( array_to_sort, size-1 );

  cout << "Number of comparisons: " << c << endl;
  cout << "Number of swaps: " << s << endl;

  //// End edited code
}

/*  Quicksort:  Sort an array a, using the quicksort
 *  algorithm.
 */

void Quicksort( aType a[], int first, int last ) 
{
    int pivot;

    if( first < last ) {
        pivot = Pivot( a, first, last );
        Quicksort( a, first, pivot-1 );
        Quicksort( a, pivot+1, last );
    }
}


/*  Pivot:  Find and return the index of pivot element.
 */

int Pivot( aType a[], int first, int last ) 
{
    int  p = first;
    aType pivot = a[first];

    for( int i = first+1 ; i <= last ; i++ ) {
        c++;//// Added comparison count
        if( a[i] <= pivot ) {
            p++;
            Swap( a[i], a[p] );
        }
    }

    Swap( a[p], a[first] );

    return p;
}


/*  Swap:  Swap two item (by reference).
 */

void  Swap( aType &v1, aType &v2 )
{
    aType  tmpVal;

    s++; //// Added to swap count

    tmpVal = v1;
    v1 = v2;
    v2 = tmpVal;
}


/*  PrintArray:  Print contents of an array.
 */

void  PrintArray( aType A[], int nElements )
{
    cout << "[ ";

    for( int i = 0 ; i < nElements ; i++ )
    {
        cout << A[i] ;
        if( i < nElements-1 )
           cout << ", ";
    }

    cout << " ] " << endl;
}

