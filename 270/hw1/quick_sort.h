#include <stdio.h>


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

  // Copy contents of inArr to a new array
  int newArr[arrSize];
  for (int i=0; i<arrSize; i++) {
    newArr[i] = inArr[i];
  }

  int pivot = first+(newSize)/2;
  int i = first;
  int j = last;
  // Find first value of i less than the pivot
  while (i <= pivot) {
    if (newArr[i] >= newArr[pivot]) {

      // Find value of j less than pivot
      while (1) {
        if (newArr[j] <= newArr[pivot]) {
          int temp = newArr[j];
          newArr[j] = newArr[i];
          newArr[i] = temp;

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
  quick_sort_rec(newArr, arrSize, first, pivot-1);
  printf("%i ", newArr[pivot]);
  quick_sort_rec(newArr, arrSize, pivot+1, last);

  return 0;
}

// This is just a wrapper function for quick_sort_rec. This will call the 
// recursive part of the function
int quick_sort(int inArr[], int arrSize) {
  printf("Quick_sort: \n");
  quick_sort_rec(inArr, arrSize, 0, arrSize-1);
}
