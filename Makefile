CC=gcc
CXX=g++
CFLAGS=-std=c11 -g -O3 -Wall
LDFLAGS=-pthread
CXXFLAGS=-std=c++11 -g -O3 -Wall

all: test example debug

debug:
	$(CXX) $(CXXFLAGS) libdd_test.cpp
	valgrind --tool=memcheck\
			--leak-check=full\
			--show-leak-kinds=all\
			--track-origins=yes\
			--verbose\
			--log-file=valgrind-out.log\
			./a.out

example:
	# TODO

test:
	$(CXX) $(CXXFLAGS) libdd_test.cpp -o libdd_test.out
	./libdd_test.out

clean:
	rm *.out
	rm valgrind-out.log
