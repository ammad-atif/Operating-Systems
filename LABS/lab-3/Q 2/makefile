main: main.o functions.o
	g++ main.o function.o -o main
main.o: main.cpp   
	g++ -c main.cpp
functions.o: function.cpp
	g++ -c function.cpp
clean:
	rm *.o main

