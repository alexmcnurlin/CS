all: main.o bubble_sort.o quicksort.o insertion_sort.o
	gcc -O main.o bubble_sort.o quicksort.o insertion_sort.o -o hw1

main.o: main.c
	gcc -Oc main.c

bubble_sort.o: bubble_sort.c
	gcc -Oc bubble_sort.c

quicksort.o: quicksort.c
	gcc -Oc quicksort.c

insertion_sort.o: insertion_sort.c
	gcc -Oc insertion_sort.c
