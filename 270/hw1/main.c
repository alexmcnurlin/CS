// Alex McNurlin
// 9/14/16
// CS270
// main.c

#include <stdio.h>
#include <stdlib.h>
#include "quicksort.h"
#include "bubble_sort.h"
#include "insertion_sort.h"

int newArr[] = {4, 5, 7, 4, 3, 1, 23, 54, 65, 123, 34, 234};
int arrSize = sizeof(newArr)/sizeof(newArr[0]);

// Takes integers as command line arguments and sorts them using various methods 
int main(int argc, char* argv[]) {
  // map arguments into an int array
  //int newArr[argc];
  //int arrSize = argc-1;
  //for (int i=1; i<argc; i++) {
  //  newArr[i-1] = atoi(argv[i]);
  //}
  
  bubble_sort(newArr, arrSize);
  insertion_sort(newArr, arrSize);
  quicksort(newArr, arrSize);

  return 0;
}
