// Alex McNurlin
// CS270
// HW1
// 9/14/16

#include <stdlib.h>
#include <stdio.h>
#include "quick_sort.h"
#include "bubble_sort.h"
//#include <insertion_sort.c>

int main() {
  int arrToSort[20] = {5, 3, 6, 7, 8, 6, 4, 6, 8, 6, 4, 4, 6, 7, 8, 8, 5, 4, 3, 5};

  //bubble_sort(arrToSort, 19);
  quick_sort(arrToSort, 19, 0, 18);
}
