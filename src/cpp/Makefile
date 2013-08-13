CFLAGS=-O3

all: cppca cppserver

cppca: cppca.cpp test_ca.cpp cppca.h
	g++ $(CFLAGS) cppca.cpp test_ca.cpp -o cppca

cppserver: cppserver.cpp
	g++ $(CFLAGS) cppserver.cpp -lzmq -o cppserver
