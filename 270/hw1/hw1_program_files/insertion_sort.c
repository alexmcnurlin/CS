// Alex McNurlin
// 9/14/16
// CS270
// insertion_sort.h

#include <stdio.h>
#include <stdlib.h>
#include "insertion_sort.h"

// Implements an insertion sort
int insertion_sort(int input[], int inputc) {
  printf("Insertion sort: \n");

  for (int i=1; i<inputc; i++) {
    for (int j=i; j>0; j--) {
      while (input[j] < input[j-1]) {
        int temp = input[j];
        input[j] = input[j-1];
        input[j-1] = temp;
      }
    }
  }

  for (int i=0; i<inputc; i++) {
    printf("%i ", input[i]);
  }
    printf("\n");
}
