// Alex McNurlin
// 9/14/16
// CS270
// bubble_sort.c

#include <stdio.h>
#include <stdlib.h>
#include "bubble_sort.h"

// Accepts an array of integers and prints the sorted array to the screen
int bubble_sort(int input[], int inputc) {

  for (int i=inputc; i>0; i--) {
    for (int j=0; j<i-1; j++) {
      if (input[j] > input[j+1]) {
        int temp = input[j];
        input[j] = input[j+1];
        input[j+1] = temp;
      }
    }
  }

  printf("%s\n", "Bubble Sort: ");
  for (int i=0; i<inputc; i++) {
    printf("%i ", input[i]);
  }
  printf("\n");
  return 0;
}
