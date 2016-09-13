// Alex McNurlin
// 9/14/16
// CS270
// quicksort.h

#ifndef QUICK_H
extern int newArr[];
extern int arrSize;
int quicksort(int* input, int inputc);
int quick_sort_rec(int inArr[], int arrSize, int first, int last);
#endif
