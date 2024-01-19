all := main

main:
	g++ -std=c++20 -fmodules-ts -xc++-system-header iostream
	g++ -std=c++20 -fmodules-ts -c Math.cc 
	g++ -std=c++20 -fmodules-ts -c main.cpp
	g++ main.o Math.o

