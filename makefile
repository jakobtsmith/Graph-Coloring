main: main.o functions.o
	g++ -std=c++11 -o main main.o functions.o
main.o: main.cpp functions.h
	g++ -std=c++11 -c main.cpp
functions.o: functions.h functions.cpp
	g++ -std=c++11 -c functions.cpp
