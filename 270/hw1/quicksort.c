// Alex McNurlin
// 9/14/16
// CS270
// quicksort.c

#include <stdio.h>
#include <stdlib.h>

int quick_sort_rec(int inArr[], int arrSize, int first, int last);

int main(int argc, char* argv[]) {
  printf("Quicksort: \n");

  // map arguments into an int array
  int input[argc];
  int inputc = argc-1;
  for (int i=1; i<argc; i++) {
    input[i-1] = atoi(argv[i]);
  }

  quick_sort_rec(input, inputc, 0, inputc-1);

  printf("\n");
}


// Performs a quicksort on the given array
// Takes array, array size, and first/last indices as arguments
// Doesn't modify original array
int quick_sort_rec(int inArr[], int arrSize, int first, int last) {
  // arrSize is the total size of the array. newSize is the size of the portion
  // we're sorting
  int newSize = last-first+1;
  // Break on base case
  if (newSize < 1) {
    return 0;
  } else if (newSize == 1) {
    printf("%i ", inArr[first]);
    return 0;
  }

  int pivot = first+(newSize)/2;
  int i = first;
  int j = last;
  // Find first value of i less than the pivot
  while (i <= pivot) {
    if (inArr[i] >= inArr[pivot]) {

      // Find value of j less than pivot
      while (1) {
        if (inArr[j] <= inArr[pivot]) {
          int temp = inArr[j];
          inArr[j] = inArr[i];
          inArr[i] = temp;

          // If the pivot is being moved, change the index of the pivot to match
          if (i == pivot) {
            pivot = j;
          } else if (j == pivot) {
            pivot = i;
          }

          break;
        }
        j--;

      }
    }
    i++;

    if (i==j) {
      break;
    }
  }

  // recursively call the sort on each half. 
  // The value will be printed using an in-order traversal
  quick_sort_rec(inArr, arrSize, first, pivot-1);
  printf("%i ", inArr[pivot]);
  quick_sort_rec(inArr, arrSize, pivot+1, last);

  return 0;
}

