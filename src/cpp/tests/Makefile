CPP=g++
CFLAGS=-I $(HOME)/local/include -L $(HOME)/local/lib
LIBS=-lgtest -lpthread

all: gtca test_gridman

gtca: gt.cpp ../cppca.cpp ../cppca.h
	$(CPP) gt.cpp ../cppca.cpp -L . $(CFLAGS) $(LIBS) -o gtca

test_gridman: test_gridman.cpp ../gridmanager.cpp ../gridmanager.h
	$(CPP) test_gridman.cpp ../gridmanager.cpp -L . $(CFLAGS) $(LIBS) -o test_gridman
