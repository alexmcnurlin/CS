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
  int arrSize = 20;
  int arrToSort[] = {5, 234, 73, 8, 1, 2345, 345, 76, 23, 454, 3, 2, 3, 5, 5, 78, 354, 2, 2345, 35};

  quick_sort(arrToSort, arrSize, 0, arrSize-1);
}
