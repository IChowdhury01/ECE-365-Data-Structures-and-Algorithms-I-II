// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II
// Graph Header

#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <climits>

class graph {

  public:

    graph(int capacity=100);  // Graph constructor. Default capacity = 100

    void Dijkstra(std::string Vsource); // Implementation of Dijkstra's algorithm. Finds the least-cost path from the source vertex to each other vertex in the graph.

    void insertE(std::string start, std::string end, int distance); // Inserts an edge between the specified start and end vertex ids, with the specified cost (distance).

    bool insertV(std::string id); // Inserts a vertex into the graph, with the specified string id. Returns false if the vertex already exists.

    bool checkV(std::string id);  // Checks if a vertex with the specified id already exists within the graph. Returns true if it exists, and false if it doesn't.

    void writePath(std::string filename); // Writes the output file to the specified path. 

    /* 
    File contents:
    Vertices are listed in the order they were stored.
    Each line lists a vertex and the least-cost path from the source vertex to it.
    */

  private:
    class edge; // Nested edge class

    class vertex {  // Nested vertex class
      public:
        std::string name;
        std::list<edge *> adj;
        vertex *Vprev;
        bool vertexKnown;
        int distance;
    };

    class edge {
      public:
        vertex *Vdest;
        int edgeCost;
    };

    std::list<vertex *> vertex_list;
    hashTable *vertex_map;
};

#endif