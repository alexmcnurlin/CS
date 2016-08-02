/*  mergeSort.cpp
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

typedef int aType;   //  array type

const int MAX_ARRAY = 10000;    //// This was bumped up to be big enough

    //  prototypes
void  Mergesort( aType a[], int first, int last );
void  Merge( aType a[], 
             int firstLeft,  int lastLeft, 
             int firstRight, int lastRight );

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
    cout << "File " << filename << " is invalid " << endl << "Exiting..." << endl;
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
  // for some reason, the program always reads in one more line thats empty. This fixes that
  size--;

  cout << "Sorting..." << endl;
  Mergesort( array_to_sort, 0, size-1 );
  PrintArray( array_to_sort, size-1 );

  cout << "Number of comparisons: " << c << endl;
  cout << "Number of swaps: " << s << endl;

  //// End edited code

    ////cout << "\nFinal array contents:" << endl;
    ////PrintArray( testArray, nA );
}


/*  Mergesort:  Do a mergesort on array a.  
 *  Note:  This is a recursive routine.
 */

void Mergesort( aType a[], int first, int last ) 
{
    int  middle;

    ////cout << "\nMergesort:" << endl;
    ////cout << "Mergesort::first: " << first << endl;
    ////cout << "Mergesort::last:  " << last  << endl;

    if( first < last ) {
        middle = (first + last)/2;
        cout << "Mergesort::middle:  " << middle << endl;
        Mergesort( a, first, middle);
        Mergesort( a, middle+1, last );
        Merge( a, first, middle, middle+1, last );
    }
}

/*  Merge:  Merge two segments of an array together.  
 */

void Merge( aType a[], 
            int firstLeft,  int lastLeft, 
            int firstRight, int lastRight ) 
{
    aType tempArray[MAX_ARRAY];
    int  index = firstLeft;
    int  firstSave = firstLeft;

    ////cout << "Merge::firstLeft:  " << firstLeft   << endl;
    ////cout << "Merge::lastLeft:   " << lastLeft    << endl;
    ////cout << "Merge::firstRight: " << firstRight  << endl;
    ////cout << "Merge::lastRight:  " << lastRight   << endl;

        //  Merge segments (array subsets)
    while( (firstLeft <= lastLeft) && (firstRight <= lastRight) )
    {
        c++;//// Added comparison count
        if( a[firstLeft] < a[firstRight] )
        {
           tempArray[index] = a[firstLeft];
           firstLeft++;
        }
        else
        {
           s++; //// Added swap count
           tempArray[index] = a[firstRight];
           firstRight++;
        }
        index++;
    }
        //  Copy remainder of left array into tempArray
    while( firstLeft <= lastLeft )
    {
        tempArray[index] = a[firstLeft];
        firstLeft++;
        index++;
    }

        //  Copy remainder of right array into tempArray
    while( firstRight <= lastRight )
    {
        tempArray[index] = a[firstRight];
        firstRight++;
        index++;
    }

        //  Copy back into original array
    for( index = firstSave ; index <= lastRight ; index++ )
        a[index] = tempArray[index];
}


/*  Swap:  Swap two items (by reference).
 */
void  Swap( aType &v1, aType &v2 )
{
    aType  tmpVal;

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
