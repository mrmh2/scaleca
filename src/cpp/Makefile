CFLAGS=-Ofast -fopenmp
CPP=g++
CXX=g++

all: cppca cppserver time_ca make_states parca

parca: cppca.cpp parca.cpp cppca.h
	$(CXX) $(CFLAGS) cppca.cpp parca.cpp -o parca

make_states: cppca.cpp make_states.cpp cppca.h
	$(CXX) $(CFLAGS) cppca.cpp make_states.cpp -o make_states

time_ca: cppca.cpp time_ca.cpp cppca.h
	$(CPP) $(CFLAGS) cppca.cpp time_ca.cpp -o time_ca

cppca: cppca.cpp test_ca.cpp cppca.h
	g++ $(CFLAGS) cppca.cpp test_ca.cpp -o cppca

cppserver: cppserver.cpp
	g++ $(CFLAGS) cppserver.cpp -lzmq -o cppserver

clean:
	rm -f cppserver cppca time_ca
