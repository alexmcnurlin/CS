/* Hash.cpp
 *
 *  Hash table implementation from:
 *  Kernighan & Ritchie, The C Programming Language,
 *     Second Edition, Prentice-Hall, 1988.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "hash.h"


const int HASH_TABLE_SIZE = 100;
static NListPtr hashTable[HASH_TABLE_SIZE];

    //  Prototypes
static char *Strdup( const char * );  //  in cstring, but....



/*  Hash
 *  Generate hash value for string s
 */

unsigned Hash( char *s )
{
    unsigned hashVal;
    
    for( hashVal = 0 ; *s != '\0' ; s++ )
        hashVal = *s + 31 * hashVal;
        
    return  hashVal % HASH_TABLE_SIZE;
}


/*  Lookup
 *  Look for s in hashTable
 */

NListPtr Lookup( char *s )
{
    NListPtr np;
    
    for( np = hashTable[Hash(s)] ; np != NULL ; np = np->next )
    {
        if( strcmp(s, np->name) == 0 )
            return np;    //  found
    }
    
    return NULL;          //  not found
}


// Similar to lookup, but prints results to the screen
NListPtr Lookup_with_output( char *s )
{
    NListPtr np;
    
    int i = 0;
    for( np = hashTable[Hash(s)] ; np != NULL ; np = np->next )
    {
        i++;
        if( strcmp(s, np->name) == 0 ) {
            cout << "Found \"" << s << "\" in bucket " << Hash(s) << ". " << i << " probes requred" << endl;
            return np;    //  found
        }
    }

    cout << "\"" << s << "\" not found." << endl;
    
    return NULL;          //  not found
}

/*  Insert
 *  Put name in hash table
 */
 
NListPtr Insert( char *name )
{
    unsigned hashVal;
    NListPtr np;
    
    if( (np = Lookup(name)) == NULL )  // not found
    {
        np = (NListPtr) malloc(sizeof(*np));
        if( np == NULL || (np->name = Strdup(name)) == NULL )
            return NULL;
        hashVal = Hash(name);
        np->next = hashTable[hashVal];
        hashTable[hashVal] = np;
    }
    
    return np;
}


/*  PrintHashTable
 *  Print the hash table contents
 */

void PrintHashTable()
{
    NListPtr np;

    cout << "Hash table contents:" << endl;
    cout << "--------------------\n" << endl;

    for( int i = 0 ; i < HASH_TABLE_SIZE ; i++ )
    {
        np = hashTable[i];
        while( np != NULL )
        {
             cout << setw(3) << i << ":    ";
             cout << np->name;
             cout << endl;
             np = np->next;
        }
    }
}


/*  Strdup
 *  Make a duplicate copy of s
 */

static char *Strdup( const char *s )
{
    char *p;
    
    p = (char *) malloc(strlen(s)+1);  /*  +1 for '\0'  */
    if( p != NULL )
        strcpy(p,s);

    return p;
}

// Count the number of items in each bucket and print to the screen
void CountHashTable() {
    NListPtr np;
    int k = 0;

    cout << "Hash table Bucket Size:" << endl;
    cout << "--------------------\n" << endl;

    // Count the number of items in each bucket
    for( int i = 0 ; i < HASH_TABLE_SIZE ; i++ )
    {
        np = hashTable[i];
        int j = 0;
        while( np != NULL )
        {
            j++;
            np = np->next;
        }

        if ( j == 0 ) {
          k++;
        }
        cout << i << ": " << j << " items" << endl;
    }
    cout << k << " buckets had no contents" << endl;
}

// Finds the bucket with the most entries and the least
void HashMinMax() {
    NListPtr np;
    // minimum and maximum keys/values
    int min_i = -1;
    int min_j = 0;
    int max_i = -1;
    int max_j = 0;


    for( int i = 0 ; i < HASH_TABLE_SIZE ; i++ )
    {
        np = hashTable[i];
        int j = 0;
        while( np != NULL )
        {
            j++;
            np = np->next;
        }

        // Set the min and max to the first if it hasn't been set yet
        if ( min_i == -1 ) {
          min_i = i;
          min_j = j;
          max_i = i;
          max_j = j;
        } else if ( j < min_j ) { // Set min value
          min_j = j;
          min_i = i;
        } else if ( j > max_j ) { // Set max value
          max_j = j;
          max_i = i;
        }


    }

    // Print results
    cout << "Max: Bucket " << max_i << " has " << max_j << " nodes" << endl;
    cout << "Min: Bucket " << min_i << " has " << min_j << " nodes" << endl;
}
