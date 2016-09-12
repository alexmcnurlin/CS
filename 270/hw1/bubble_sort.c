// Alex McNurlin
// 9/14/16
// CS270
// bubble_sort.c

#include <stdio.h>
#include <stdlib.h>

// Accepts an array of integers and prints the sorted array to the screen
int main(int argc, char* argv[]) {
  // map arguments into an int array
  int newArr[argc];
  int arrSize = argc-1;
  for (int i=1; i<argc; i++) {
    newArr[i-1] = atoi(argv[i]);
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
