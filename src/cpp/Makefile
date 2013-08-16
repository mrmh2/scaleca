CFLAGS=-O3 -fopenmp
CPP=g++
CXX=g++
MPICXX=mpic++

all: cppca cppserver time_ca griddev make_states mpica parca

mpica: cppca.cpp gridmanager.cpp cppca.h gridmanager.h mpica.cc
	$(MPICXX) -O3 cppca.cpp gridmanager.cpp mpica.cc -o mpica

parca: cppca.cpp parca.cpp gridmanager.cpp cppca.h
	$(CXX) $(CFLAGS) cppca.cpp parca.cpp gridmanager.cpp -o parca

make_states: cppca.cpp make_states.cpp cppca.h
	$(CXX) $(CFLAGS) cppca.cpp make_states.cpp -o make_states

griddev: griddev.cpp gridmanager.cpp gridmanager.h
	$(CPP) $(CFLAGS) griddev.cpp gridmanager.cpp -o griddev

time_ca: cppca.cpp time_ca.cpp cppca.h
	$(CPP) $(CFLAGS) cppca.cpp time_ca.cpp -o time_ca

cppca: cppca.cpp test_ca.cpp cppca.h
	g++ $(CFLAGS) cppca.cpp test_ca.cpp -o cppca

cppserver: cppserver.cpp
	g++ $(CFLAGS) cppserver.cpp -lzmq -o cppserver

clean:
	rm -f cppserver cppca time_ca
