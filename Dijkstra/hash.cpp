// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II
// Hash Table Class
#include <iostream>

#include "hash.h"   // include header file


using namespace std;

hashTable::hashTable(int size) {    // Constructor initializes the hash table.
    capacity = getPrime(size);  
    data.resize(capacity);
    filled = 0;

    int i = data.size() - 1;
    while(i >= 0) {
        data[i].isOccupied = false;
        i--;
    }
}

bool hashTable::contains(const std::string &key) {  // Checks if the specified key is in the hash table.
    int pos = findPos(key);

    if (pos == -1)
        return false;
    else
        return true;
}

int hashTable::insert(const std::string &key, void *pv) {   // Inserts specified key into hash table
    bool success_test;  // Tests if rehash was succesful. Returns 2 otherwise.
    int hlocation = hash(key);   

    if (contains(key))
        return 1;

    if (filled >= capacity/2) {
        success_test = rehash();
        if (!success_test)
            return 2;
    }


    while (data[hlocation].isOccupied) {    
        hlocation++;
        hlocation %= capacity;
    }

    if (!data[hlocation].isOccupied || data[hlocation].isDeleted) {
        filled++;
        data[hlocation].key = key;
        data[hlocation].isOccupied = true;
        data[hlocation].isDeleted = false;
        data[hlocation].pv = pv;
        return 0;
    }

    return -1;
}

bool hashTable::remove(const std::string &key) {    // Deletes the item with the specified key
    int pos = findPos(key);

    if (pos == -1)
        return false;
    else {
        data[pos].isDeleted = true;
        return true;
    }
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int pos = findPos(key);

    if (pos == -1)
        return 1;
    else {
        data[pos].pv = pv;
        return 0;
    }
}

void* hashTable::getPointer(const std::string &key, bool *ptr) {    // Retrievse pointer associated with the specified key
    int pos = findPos(key);

    if (pos == -1 || data[pos].isDeleted) {
        *ptr = false;
        return NULL;
    }
    else {
        *ptr = true;
        return data[pos].pv;
    }
}

int hashTable::hash(const std::string &key) {   // Hash function. 
// The hash function is used to map the search key to a list; the index gives the place in the hash table where the corresponding record should be stored. 
    int hVal = 0;   // Initial hash value

    int i = key.length() - 1;
    while(i >= 0) {
        hVal = key[i] + (31 * hVal);    // Source: https://www.cs.princeton.edu/~rs/AlgsDS07/10Hashing.pdf
        i--;
    }

    hVal %= capacity;
    if (hVal < 0)
        hVal += capacity;

    return hVal;
}

// Rehash function uses linear probing for collision aversion
bool hashTable::rehash() {  // Copies old values into a temporary hash table, expands and resets hash table, then re-enters values. 
    try {
        vector<hashItem> osize = data;  // old size value
        filled = 0;

        int nsize = getPrime(capacity); // new size value
        data.clear();
        data.resize(nsize);
        capacity = nsize;

        for (int i=capacity-1; i>=0; i--) {
            data[i].isOccupied = false;
        }

        int i = osize.size() - 1;
        while (i >= 0) {
            if (osize[i].isOccupied && !osize[i].isDeleted) {
                    insert(osize[i].key, osize[i].pv);
                }
            i--;
        }

        osize.clear();
        return true;
    }
    catch (const bad_alloc &ptr) {
        cerr << "Memory Allocation Failed." << endl;
        return false;
    }
}

int hashTable::findPos(const std::string &key) {    // Searches for an item with the specified key. Returns the position of the item if found.
    int hVal = hash(key);
    if (!data[hVal].isOccupied)
        return -1;

    while (data[hVal].isOccupied) {                            
        if (data[hVal].key == key && !data[hVal].isDeleted)
            return hVal;

        hVal++;
        hVal %= capacity;
    }
    return -1;
}

unsigned int hashTable::getPrime(int size) {    // Returns a prime number at least as large as size
    vector<int> primenums;

    primenums.push_back(196613);    // List of hash table primes. Source: https://planetmath.org/goodhashtableprimes
    primenums.push_back(393241);
    primenums.push_back(786433);
    primenums.push_back(1572869);
    primenums.push_back(3145739);
    primenums.push_back(6291469);
    primenums.push_back(12582917);

    int i = 0;
    while(i < primenums.size()) {
        if (primenums[i] > size) {
            return primenums[i];
        }
    i++;
    }
    return 0;
}