// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II

#include <iostream>
#include <fstream>
#include <sstream>

#include <ctime>
#include <algorithm>

#include "hash.h"


using namespace std;

hashTable dictionary(50000);    // Initial size of hash table    

int spellCheck(ifstream &input, ofstream &output);  // Spell-check and dictionary loading functions
void loadDictionary(ifstream &dict_file);

int main() {
    string filename, outfilename;   // Asks user for dictionary file
    cout << "Enter dictionary file name: ";
    cin >> filename;

    ifstream input(filename.c_str());   // Creates input filestream
    if (!input) {
        cerr << "Error: failed to open " << filename << endl;
        exit(1);
    }

    clock_t t1 = clock();   // Times dictionary loading
    loadDictionary(input);
    clock_t t2 = clock();

    double timeDict = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Dictionary load time (in seconds): ";
    cout << timeDict << endl;

    input.close();

    cout << "Enter input file name: ";  // Asks user for the input file to be spell-checked.
    cin >> filename;

    cout << "Enter output file name: "; // Asks for name of output file to be written to.
    cin >> outfilename;

    ifstream spellInput(filename.c_str());
    ofstream output(outfilename.c_str());

    t1 = clock();   // Times spell checking process
    int spellCheckSuccess = spellCheck(spellInput, output);
    t2 = clock();

    double timeSpellcheck = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time to check document (seconds): ";
    cout << timeSpellcheck << endl;

    return 0;
}


int spellCheck(ifstream &input, ofstream &output) {
    string characters="abcdefghijklmnopqrstuvwxyz0123456789\'-";    // String of all valid characters - alphabet, digits, dashes, and apostraphes
    string digits="0123456789";
    string nextLine, nextWord;
    int lineNum = 1, start, end;    // Line count

    while (getline(input, nextLine)) {
        transform(nextLine.begin(), nextLine.end(), nextLine.begin(), ::tolower);   // Transforms to lower case

        if (nextLine=="") { // Skips blank lines
            lineNum++;
            continue;
        }

        for (start = nextLine.find_first_of(characters); start != string::npos;) {  // Treat all invalid characters as word separators, including spaces
            end = nextLine.find_first_not_of(characters, start);
            nextWord = nextLine.substr(start,end-start);
            start = nextLine.find_first_of(characters, end);

            if (nextWord.length() > 20) {   // Identifies long words (over 20 characters)
                output << "Long word at line ";
                output << lineNum;
                output << ", starts: ";
                output << nextWord.substr(0,20) << endl;
            }

            else if (nextWord.find_first_of(digits) != string::npos)    // Skips words with numbers
                continue;

            else if (!dictionary.contains(nextWord)) {  // Identifies words that aren't in the dictionary file
                output << "Unknown word at line ";
                output << lineNum;
                output << ": " << nextWord << endl;
            }

            if (end == string::npos)    // Breaks at the end of a line
                break;
        }
        lineNum++;  // Increment line count
    }
    return 0;
}

void loadDictionary(ifstream &dict_stream) {    
    string nextWord;
    while (getline(dict_stream, nextWord)) {
        transform(nextWord.begin(), nextWord.end(), nextWord.begin(), ::tolower);
        dictionary.insert(nextWord);
    }
    return;
}