all: main.o bubble_sort.o quicksort.o insertion_sort.o
	gcc main.o bubble_sort.o quicksort.o insertion_sort.o -o hw1

main.o: main.c
	gcc -c main.c

bubble_sort.o: bubble_sort.c
	gcc -c bubble_sort.c

quicksort.o: quicksort.c
	gcc -c quicksort.c

insertion_sort.o: insertion_sort.c
	gcc -c insertion_sort.c

#bubble_sort: bubble_sort.c
#	gcc bubble_sort.c -o bubble_sort
#
#insertion_sort: insertion_sort.c
#	gcc insertion_sort.c -o insertion_sort
#
#quicksort: quicksort.c
#	gcc quicksort.c -o quicksort
