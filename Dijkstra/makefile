Dijkstra.exe: main.cpp Graph.o Heap.o hash.o
	g++ -std=c++11 -o Dijkstra.exe main.cpp Graph.o Heap.o hash.o

Graph.o: Graph.cpp Graph.h
	g++ -std=c++11 -c Graph.cpp

Heap.o: Heap.cpp Heap.h
	g++ -std=c++11 -c Heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o debug.exe main.cpp Graph.cpp Heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~
