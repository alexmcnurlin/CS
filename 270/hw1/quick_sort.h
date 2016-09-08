#include <stdio.h>


// Performs a quicksort on the given array
// Takes array, array size, and first/last indices as arguments
// Doesn't modify original array
int quick_sort(int inArr[], int arrSize, int first, int last) {
  // Copy contents of inArr to a new array
  int newArr[arrSize];
  for (int i=0; i<arrSize; i++) {
    newArr[i] = inArr[i];
  }

  int pivot = first+(arrSize)/2;
  //int pivot = newArr[pivot_i];

  int i = first;
  int j = last;
  while (i <= pivot) {
    if (newArr[i] >= newArr[pivot]) {

      int swapped = 0;
      while (!swapped) {

        if (newArr[j] < newArr[pivot]) {
          int temp = newArr[j];
          newArr[j] = newArr[i];
          newArr[i] = temp;

          if (i == pivot) {
            pivot = j;
          }

          swapped = 1;
        }
        j--;

      }
    }
    i++;

    if (i==j) {
      break;
    }
  }

  /* size1 = pivot-first; */
  /* size2 = last-pivot */
  quick_sort(newArr, pivot-first, first, pivot-1);
  printf("%i ", newArr[pivot]);
  quick_sort(newArr, last-pivot, pivot+1, last);

  return 0;
}
