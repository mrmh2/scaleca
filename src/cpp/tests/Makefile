CPP=g++
CFLAGS=-I $(HOME)/local/include -L $(HOME)/local/lib -fopenmp
LIBS=-lgtest -lpthread

gtca: gt.cpp ../cppca.cpp ../cppca.h
	$(CPP) gt.cpp ../cppca.cpp -L . $(CFLAGS) $(LIBS) -o gtca
