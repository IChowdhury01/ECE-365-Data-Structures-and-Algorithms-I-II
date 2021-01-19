// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2018

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  unsigned int val1;
  unsigned int val2;
  char val3;
  string val4;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename.c_str());
  if (!input) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->val1 >> pData->val2 >> pData->val3 >> pData->val4;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename.c_str());
  if (!output) {
    cerr << "Error: could not open " << filename << endl;
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << endl;

  // Write the data
  for (list<Data *>::const_iterator ipD = l.begin(); ipD != l.end(); ipD++) {
    output << (*ipD)->val1 << " " 
	   << (*ipD)->val2 << " " 
	   << (*ipD)->val3 << " " 
	   << (*ipD)->val4 << endl;
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &, int field);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.  Executing sort..." << endl;

  int field = 0;
  cout << "Enter an integer from 1 - 4, representing field to sort: ";
  try {
    cin >> field;
    if (field < 1 || field > 4) {
      cerr << "Error: invalid field" << endl;
      exit(1);
    }
  }
  catch (...) {
    cerr << "Error: invalid field" << endl;
    exit(1);
  }
    
  clock_t t1 = clock();
  sortDataList(theList, field);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds." << endl;

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

void sortDataList(list<Data *> &l, int field) {
  if( field == 1) {
	  l.sort([]( Data * a,  Data * b) { return a->val1 < b->val1; });
  }
  else if( field == 2) {
	  l.sort([]( Data * a,  Data * b) { return a->val2 < b->val2; });
  }
  else if( field == 3) {
	  l.sort([]( Data * a,  Data * b) { return a->val3 < b->val3; });
  }
  else if( field == 4) {
	  l.sort([]( Data * a,  Data * b) { return a->val4 < b->val4; });
  }
}

// 1) Insertion sort (TB)
// 2) Built-in sort
// 3) Radix Sort
// 4) Radix Sort on vector (TB)


/**1
* Simple insertion sort.
// */
// void insertionSort( list<Data*> & l )
// {

// for( int p [] = {}; p < l.size( ); ++p )
// {
// Data tmp = std::move( l[ p ] );
// temp->val1 = array[p]->val1;
// int j;
// for( j = p; j > 0 && tmp < l[ j - 1 ]; --j )
//  l[ j ] = std::move( l[ j - 1 ] );
//  l[ j ] = std::move( tmp );
//  }
//  }


// 4
// void sortDataList(list<Data *> &l, int field) {
//   // Fill in this function
// }

// /*
// * Radix sort an array of Strings
// * Assume all are all ASCII
// * Assume all have same length
// */
// void radixSortA( vector<Data*> & arr, int stringLen )
// {
// const int BUCKETS = 128;
// vector<vector<Data*>> buckets( BUCKETS );

// stringLen = 5;
//  for( int pos = stringLen - 1; pos >= 0; --pos )
//  {
  
//  for( string & s : arr )
//  buckets[ s[ pos ] ].push_back( std::move( s ) ) -> val4;

//  int idx = 0;
//  for( auto & thisBucket : buckets )
//  {
//  for( string & s : thisBucket )
//  arr[ idx++ ] = std::move( s );

//  thisBucket.clear( );
//  }
//  }
//  }
