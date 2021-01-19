useGraph.exe: useGraph.o hash.o heap.o graph.o
	g++ -o useGraph.exe hash.o heap.o useGraph.o graph.o

useGraph.o: useGraph.cpp
	g++ -c useGraph.cpp

heap.o: heap.cpp heap.h
	g++ -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -c graph.cpp

clean:
	rm -rf *.o *.exe