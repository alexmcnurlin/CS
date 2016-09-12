// Alex McNurlin
// 9/14/16
// CS270
// insertion.c

#include <stdio.h>
#include <stdlib.h>

// Implements an insertion sort
int main(int argc, char* argv[]) {
  printf("Insertion sort: \n");

  // map arguments into an int array
  int input[argc];
  int inputc = argc-1;
  for (int i=1; i<argc; i++) {
    input[i-1] = atoi(argv[i]);
  }

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
