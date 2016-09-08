#include <stdio.h>


// Performs a quicksort on the given array
// Takes array, array size, and first/last indices as arguments
// Doesn't modify original array
int quick_sort_rec(int inArr[], int arrSize, int first, int last) {
  //printf("arrSize %i, first %i, last %i\n", arrSize, first, last);

  int newSize = last-first+1;
  if (newSize < 1) {
    return 0;
  } else if (newSize == 1) {
    printf("%i ", inArr[first]);
    return 0;
  }

  // Copy contents of inArr to a new array
  int newArr[arrSize];
  for (int i=0; i<arrSize; i++) {
    newArr[i] = inArr[i];
  }

  int pivot = first+(newSize)/2;
  int i = first;
  int j = last;
  while (i <= pivot) {
    if (newArr[i] >= newArr[pivot]) {

      int swapped = 0;
      while (!swapped) {
        if (newArr[j] <= newArr[pivot]) {
          int temp = newArr[j];
          newArr[j] = newArr[i];
          newArr[i] = temp;

          if (i == pivot) {
            pivot = j;
          } else if (j == pivot) {
            pivot = i;
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

  quick_sort_rec(newArr, arrSize, first, pivot-1);
  printf("%i ", newArr[pivot]);
  quick_sort_rec(newArr, arrSize, pivot+1, last);

  return 0;
}

int quick_sort(int inArr[], int arrSize, int first, int last) {
  printf("Quick_sort: \n");
  quick_sort_rec(inArr, arrSize, first, last);
}
