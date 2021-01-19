// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II
// Application of Dijkstra's Algorithm

#include "graph.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <ctime>


using namespace std;


void load(graph &myGraph, ifstream &input) {    // Reads from the given input file, and inserts the specified edges and vertices into the graph.

    int cost;
    string line, start, end;

    while (getline(input,line)) {
        istringstream stream(line);
        stream >> start >> end >> cost;

        myGraph.insertE(start,end,cost);
    }
}

int main() {
    string vStart;
    bool inputValid = false;
    string infile, outfile;

    cout << "Enter graph filename: ";   // Prompts for a graph file.
    cin >> infile;
    ifstream input(infile.c_str());
    if (!input.is_open()) { // Determines if graph file is invalid.
        cout << "Error: Invalid filename: " << infile << endl;
        exit(EXIT_FAILURE);
    }

    graph myGraph(100); // Constructs graph
    load(myGraph, input);   // Loads graph. Inserts edges and vertices into graph, according to input file.

    while (!inputValid) {   
        cout << "Enter a starting vertex id: "; // Prompts for starting vertex
        cin >> vStart;

        if (myGraph.checkV(vStart))
            inputValid = true;
        else
            cout << "Error: Invalid vertex id: " << vStart << endl; // Determines if starting vertex is invalid
    }

    clock_t start = clock();    // Time Dijkstra's algorithm runtime
    myGraph.Dijkstra(vStart);
    clock_t finish = clock();
    
    double dRunTime = ((double) (finish-start)) / CLOCKS_PER_SEC;

    cout << "Enter output filename: ";  // Prompts for name of output file
    cin >> outfile;

    myGraph.writePath(outfile); // Writes output file.

    cout << "Process completed. Total runtime for Dijkstra's algorithm (seconds): ";    // Prints runtime report.

    cout << dRunTime << endl;

    input.close();  // Close files

    return 0;
}