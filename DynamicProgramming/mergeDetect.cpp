// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II
// Detect a Merge of 2 Strings, using Dynamic Programming

/* 
ACM Programming Problem Statement:

Define a merge of two strings to be any string formed from all the characters in both strings, interspersed, but in their original order. 
For example, for the strings chocolate and chips, cchocholaiptes is a merge, but chocochilatspe or bananasplit are not. 

Create a program that will detect if a given string is a merge of two other given strings. 
For the purposes of this problem, the input strings will contain only lowercase alphabetic characters.

The input file consists of three strings A, B, and C, in that order, one string per line. 
The file contains no blank lines, and the end of the input is marked by the end of the file. 
The strings A and B will not exceed 1000 characters, and C will not exceed 2000 characters (rest assured that input cases of this length will be tested).

If C is not a merge of A and B, write a single line to the output file that reads "*** NOT A MERGE ***". 
If C is a merge, write to the output file the string C rewriften with the characters from A in uppercase. 
If more than one merge is possible, string C should be wriften with each character of A occurring as early as possible (examine the sample input below for such examples).
*/


#define SIZE 1001   // Default array length

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int mergePaths[SIZE][SIZE] = {0};   // Declare 2D Array

int main() {
    string A, B, C; // Input and filename strings
    string inFilename, outFilename;

    cout << "Enter name of input file: ";   // Prompt user for filenames
    cin >> inFilename;
    cout << "Enter name of output file: ";
    cin >> outFilename;

    ifstream in (inFilename.c_str());   // File streams
    ofstream out (outFilename.c_str());

    while (getline (in, A) && getline (in, B) && getline (in, C)) { // Read lines from infile
        int A_len, B_len, C_len;    
        int i, j;
        int x, y;

        A_len = A.length(); // String lengths
        B_len = B.length();
        C_len = C.length();

        for (i = 0; i < SIZE; i++) {    // Initialize 2D Array
            for (j = 0; j < SIZE; j++) {
                mergePaths[i][j] = 0;
            }
        }
        mergePaths[0][0] = 1;   // Initialize first element of array

        if (C_len != A_len + B_len) {   // Detect non-merges
            out << "*** NOT A MERGE ***" << endl;
            continue;
        }

        for (int x = 0; x <= A_len; x++) {  // Matrix traversal for filling in merge paths
            for (int y = 0; y <= B_len; y++) {

                if (mergePaths[x][y] == 1) {

                    if (C[x+y] == A[x])
                        mergePaths[x+1][y] = 1;
                    if (C[x+y] == B[y])
                        mergePaths[x][y+1] = 1;

                }
            }
        }

        if (mergePaths[A_len][B_len] == 1) {    // Check merge conditions
            int i = A_len;
            int j = B_len;
            while (i > 0 && j >= 0) {
                if (mergePaths[i][j] == 1 && (j == 0 || mergePaths[i][j-1] == 0)) {
                    C[i+j-1] = toupper (C[i+j-1]);  // Convert lower-case to upper-case
                    i--;
                } 
                else {
                    j--;
                }
            }
            out << C << endl;   // Print to outfile
        } 
        else {
            out << "*** NOT A MERGE ***" << endl;
        }
    }

    in.close(); // Close filestreams
    out.close();
    return 0;
}