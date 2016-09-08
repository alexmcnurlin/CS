// Alex McNurlin
// bubble_sort.c

#include <stdio.h>

// Accepts an array of integers and prints the sorted array to the screen
// Requires the size of the array as function argument
// Doesn't modify the given array
int bubble_sort(int inArr[], int arrSize) {
  // Copy contents of inArr to a new array
  int newArr[arrSize];
  for (int i=0; i<arrSize; i++) {
    newArr[i] = inArr[i];
  }

  for (int i=arrSize; i>0; i--) {
    for (int j=0; j<i-1; j++) {
      if (newArr[j] > newArr[j+1]) {
        int temp = newArr[j];
        newArr[j] = newArr[j+1];
        newArr[j+1] = temp;
      }
    }
  }

  printf("%s\n", "Bubble Sort: ");
  for (int i=0; i<arrSize; i++) {
    printf("%i ", newArr[i]);
  }
  printf("\n");
  return 0;
}
