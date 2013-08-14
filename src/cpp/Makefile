CFLAGS=-O4
CPP=clang++

all: cppca cppserver time_ca

time_ca: cppca.cpp time_ca.cpp cppca.h
	$(CPP) $(CFLAGS) cppca.cpp time_ca.cpp -o time_ca

cppca: cppca.cpp test_ca.cpp cppca.h
	g++ $(CFLAGS) cppca.cpp test_ca.cpp -o cppca

cppserver: cppserver.cpp
	g++ $(CFLAGS) cppserver.cpp -lzmq -o cppserver
