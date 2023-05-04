all:
	g++ main.cpp Structs.cpp
	./a.out truckload.txt
compile:
	g++ main.cpp g++ Structs.cpp
run:
	./a.out