CXX := clang++
CXXFLAGS := -std=c++11 -Wall -Werror -Os
OBJ := main.o Prim.o MinHeap.o

all: main

time: main
	./main

test: main
	./main "graph-10-1.txt"

debug: main
	valgrind --leak-check=full ./main "graph-10-1.txt"

debig: main
	valgrind --leak-check=full ./main "graph-100-1.txt"

runbig: main
	./main "graph-100-1.txt"

runall: main
	./main "graph-10-1.txt"
	@echo Expected result: graph-10-1:  2464
	@echo " "
	./main "graph-10-2.txt"
	@echo Expected result: graph-10-2:  2893
	@echo " "
	./main "graph-10-3.txt"
	@echo Expected result: graph-10-3:  2173
	@echo " "
	./main "graph-10-4.txt"
	@echo Expected result: graph-10-4:  1790
	@echo " "
	./main "graph-100-1.txt"
	@echo Expected result: graph-100-1: 15202

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp Prim.h MinHeap.h
	$(CXX) $(CXXFLAGS) -c main.cpp

MinHeap.o: MinHeap.cpp MinHeap.h
	$(CXX) $(CXXFLAGS) -c MinHeap.cpp

Prim.o: Prim.cpp Prim.h MinHeap.h
	$(CXX) $(CXXFLAGS) -c Prim.cpp

clean:
	rm -f main
	rm -f debug
	rm -f *.o