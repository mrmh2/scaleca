CFLAGS=-O3

all: cppca cppserver

cppca: cppca.cpp
	g++ $(CFLAGS) cppca.cpp -o cppca

cppserver: cppserver.cpp
	g++ $(CFLAGS) cppserver.cpp -lzmq -o cppserver
