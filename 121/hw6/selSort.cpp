/*  selSort.cpp
 *
 *  Selection Sort test program.
 *
 *  Bruce M. Bolden
 *  November 16, 1998
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


#define  aType  int

   //  prototypes
void  SelectionSort( aType A[], int nElements );
int IndexOfSmallest( aType A[], int iStart, int iEnd );

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

    array_to_sort[size-1] = in_int;
  } while ( !in_file.eof() );
  // for some reason, the program always reads in one more line thats empty. 
  // This fixes that
  size--;

  cout << "Sorting..." << endl;
  SelectionSort( array_to_sort, size );
  PrintArray( array_to_sort, size-1 );

  cout << "Number of comparisons: " << c << endl;
  cout << "Number of swaps: " << s << endl;

  //// End edited code
}


/*  SelectionSort:  Sort and array, A, using a selection
 *  sort algorithm.
 */

void  SelectionSort( aType A[], int nElements )
{
    int iSmallest;
    aType  tmp;
   
    cout << "------------------------" << endl;
    cout << "In SelectionSort():" << endl;

    for( int i = 0 ; i < nElements ; i++ )
    {
        cout << " Pass: " << i << endl;
        iSmallest = IndexOfSmallest( A, i, nElements-1 );
            //  swap
            
        c++;                                //// Added this line
        if( iSmallest > i )
        {
            s++;                            //// Added this line
            tmp = A[i];
            A[i] = A[iSmallest];
            A[iSmallest] = tmp;
        }

        //PrintArray( A, nElements );       //// Removed this line
    }

    cout << "SelectionSort() finished" << endl;
    cout << "------------------------" << endl;
    //PrintArray( A, nElements );
}


/*  IndexOfSmallest:  Find index of smallest value.
 */

int IndexOfSmallest( aType A[], int iStart, int iEnd )
{
    int    index = -1;
    aType  aMin = A[iStart];

    for( int i = iStart ; i <= iEnd ; i++ )
    {
        c++;
        if( A[i] < aMin )
        {
            aMin = A[i];
            index = i;
        }
    }

    cout << "IndexOfSmallest:  " << index << endl;

    return index;
}


/*  Print contents of an array.
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

