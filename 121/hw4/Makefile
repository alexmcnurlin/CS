all: hw4


hw4: bst.o hw4.o movie.o ll.o bst.h movie.h ll.h
	g++ -std=c++11 bst.o hw4.o movie.o ll.o -o hw4

hw4.o: hw4.cpp
	g++ -std=c++11 -c hw4.cpp

bst.o: bst.cpp
	g++ -std=c++11 -c bst.cpp

movie.o: movie.cpp
	g++ -std=c++11 -c movie.cpp

ll.o: ll.cpp
	g++ -std=c++11 -c ll.cpp

clean:
	rm *.o hw4
