/*  hash.h
 */

#ifndef HASH_H
#define HASH_H

struct nList     /*  table entry:  */
{
   char *name;          /*  defined name         */
   //char *defn;          /*  replacement text     */
   struct nList *next;  /*  next entry in chain  */
};

typedef struct nList *NListPtr;

unsigned Hash( char *s );
NListPtr Lookup( char *s );
NListPtr Lookup_with_output( char *s );
NListPtr Insert( char *name );

void CountHashTable();
void PrintHashTable();
void HashMinMax();

#endif  /*  HASH_H  */
