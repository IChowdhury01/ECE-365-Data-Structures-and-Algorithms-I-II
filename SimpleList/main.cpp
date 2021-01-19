/*ECE-264 Data Structures and Algorithms I Program Assignment 1
  Written by Ivan Chowdhury

  This program reads an input file given by the user and processes commands that manipulate stacks and queues.
  The results are written in an output file also given by the user.*/

#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SimpleList.h"

using namespace std;

//Create three lists that contain pointers to singly-linked lists of different types (string, int, double)
list<SimpleList<string>* > SLsContainer;
list<SimpleList<int>* > SLiContainer;
list<SimpleList<double>* > SLdContainer;

//Searches a given list for a pointer pointing to a SimpleList with the same name.
//Returns nullptr otherwise
template <typename T>
SimpleList<T>* findSimpleList(const string& name, const list<SimpleList<T>* >& slList) {
	for (SimpleList<T>* slPtr : slList) {
		if (slPtr->listName == name) {
			return slPtr;
		}
	}
	return nullptr;
}

//Parses input file, processes commands, and sends the results to the output file.
void processCommands(const string& inputFileName, const string& outputFileName) {

	//Open input and output text using ifstream and ofstream respectively.
	ifstream ifs(inputFileName, ios::in);
	ofstream ofs(outputFileName, ios::out | ios::trunc);

	//Check if the input file was opened.
	if (ifs) {
		//Each line contains at most three words: the command, the SimpleList name, and the data.
		//The first three variables will each contain their respective word.
		//The fourth will contain the entire line.
		string command, slName, data, line;

		//Retrieve every line in input text to parse.
		while (getline(ifs, line)) {

			ofs << "PROCESSING COMMAND: " << line << endl;

			//Get the command word and SimpleList name
			istringstream iss(line);
			iss >> command >> slName;

			//Create Command
			if (command == "create") {

				//Get the SimpleList type
				iss >> data;
				
				//Check if the SimpleList stores strings.
				if (slName[0] == 's') {
					
					//Check if a SimpleList with the given name already exists.
					if (findSimpleList(slName, SLsContainer) != nullptr) {
						ofs << "ERROR: This name already exists!\n";
					}
					//Check which derived object should be made.
					else if (data == "stack") {
						SimpleList<string>* SLsPtr = new Stack<string>(slName);
						SLsContainer.push_back(SLsPtr);
					}
					else if (data == "queue") {
						SimpleList<string>* SLsPtr = new Queue<string>(slName);
						SLsContainer.push_back(SLsPtr);
					}
				}

				//Check if the SimpleList stores integers.
				if (slName[0] == 'i') {
					
					//Check if a SimpleList with the given name already exists.
					if (findSimpleList(slName, SLiContainer) != nullptr) {
						ofs << "ERROR: This name already exists!\n";
					}
					//Check which derived object should be made.
					else if (data == "stack") {
						SimpleList<int>* SLiPtr = new Stack<int>(slName);
						SLiContainer.push_back(SLiPtr);
					}
					else if (data == "queue") {
						SimpleList<int>* SLiPtr = new Queue<int>(slName);
						SLiContainer.push_back(SLiPtr);
					}
				}
				//Check if the SimpleList stores doubles.
				else if (slName[0] == 'd') {

					//Check if a SimpleList with the given name already exists.
					if (findSimpleList(slName, SLdContainer) != nullptr) {
						ofs << "ERROR: This name already exists!\n";
					}
					//Check which derived object should be made.
					else if (data == "stack") {
						SimpleList<double>* SLdPtr = new Stack<double>(slName);
						SLdContainer.push_back(SLdPtr);
					}
					else if (data == "queue") {
						SimpleList<double>* SLdPtr = new Queue<double>(slName);
						SLdContainer.push_back(SLdPtr);
					}
				}
			}

			//Push Command
			else if (command == "push") {
				//Get the value being pushed into the SimpleList 
				//NOTE: This value is a string! Need to convert before pushing if necessary.
				iss >> data;

				//Check if the SimpleList stores strings.
				if (slName[0] == 's') {
					SimpleList<string>* SLsPtr = findSimpleList(slName, SLsContainer);
					//Check if there exists a SimpleList with the given name before pushing.
					if (SLsPtr != nullptr) {
						SLsPtr->push(data);
					}
					else {
						ofs << "ERROR: This name does not exist!\n";
					}
				}

				//Check if the SimpleList stores integers.
				else if (slName[0] == 'i') {
					SimpleList<int>* SLiPtr = findSimpleList(slName, SLiContainer);
					//Check if there exists a SimpleList with the given name before pushing.
					if (SLiPtr != nullptr) {
						SLiPtr->push(stoi(data));
					}
					else {
						ofs << "ERROR: This name does not exist!\n";
					}
				}

				//Check if the SimpleList stores doubles.
				else if (slName[0] == 'd') {
					SimpleList<double>* SLdPtr = findSimpleList(slName, SLdContainer);
					//Check if there exists a SimpleList with the given name before pushing.
					if (SLdPtr != nullptr) {
						SLdPtr->push(stod(data));
					}
					else {
						ofs << "ERROR: This name does not exist!\n";
					}
				}
			}

			//Pop Command
			else if (command == "pop") {
				//Check if the SimpleList stores strings.
				if (slName[0] == 's') {
					SimpleList<string>* SLsPtr = findSimpleList(slName, SLsContainer);
					//Check if there exists a SimpleList with the given name before popping.
					if (SLsPtr != nullptr) {
						//Check if the SimpleList is empty before popping.
						if (SLsPtr->getSize()) {
							ofs << "Value popped: " << SLsPtr->pop() << endl;
						}
						else {
							ofs << "ERROR: This list is empty!\n";
						}
					}
					else {
						ofs << "ERROR: This name does not exist!\n";
					}
				}

				//Check if the SimpleList stores integers.
				else if (slName[0] == 'i') {
					SimpleList<int>* SLiPtr = findSimpleList(slName, SLiContainer);
					//Check if there exists a SimpleList with the given name before popping.
					if (SLiPtr != nullptr) {
						//Check if the SimpleList is empty before popping.
						if (SLiPtr->getSize()) {
							ofs << "Value popped: " << SLiPtr->pop() << endl;
						}
						else {
							ofs << "ERROR: This list is empty!\n";
						}
					}
					else {
						ofs << "ERROR: This name does not exist!\n";
					}
				}

				//Check if the SimpleList stores doubles.
				else if (slName[0] == 'd') {
					SimpleList<double>* SLdPtr = findSimpleList(slName, SLdContainer);
					//Check if there exists a SimpleList with the given name before popping.
					if (SLdPtr != nullptr) {
						//Check if the SimpleList is empty before popping.
						if (SLdPtr->getSize()) {
							ofs << "Value popped: " << SLdPtr->pop() << endl;
						}
						else {
							ofs << "ERROR: This list is empty!\n";
						}
					}
					else {
						ofs << "ERROR: This name does not exist!\n";
					}
				}
				
			}
		}

		//Close files when finished.
		ifs.close();
		ofs.close();
	}
	else {
		ofs << "ERROR: The input file does not exist!\n";
	}
}

int main() {
	string inputFileName, outputFileName;

	cout << "Enter the name of the input file: ";
	cin >> inputFileName;

	cout << "Enter the name of the output file: ";
	cin >> outputFileName;

	processCommands(inputFileName, outputFileName);
}