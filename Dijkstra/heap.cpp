// Ivan Chowdhury
// Cooper Union EE'20
// Data Structures and Algorithms II
// Heap Class

#include <iostream>
#include "heap.h"

using namespace std;

// Initialize heap
heap::heap(int capacity) {
    mapping = new hashTable(capacity*2);
    data.resize(capacity+1);
    this->capacity = capacity;
    this->size = 0;
}

// Inserts new node into tree and percolates up to place
int heap::insert(const std::string &id, int key, void *pv) {
    if (size == capacity)
        return 1;

    else if (size < capacity && mapping->contains(id))
        return 2;

    else {
        if (size == capacity - 1)
            data.resize(capacity*2);
        size++;

        // insert node
        data[size].id = id;
        data[size].key = key;
        data[size].pData = pv;

        // insert id and pointer into hashtable
        mapping->insert(id, &data[size]);

        // percolate up to put into place
        percolateUp(size);

        return 0;
    }
}

// Sets a new key for a node of the specified ID
int heap::setKey(const std::string &id, int key) {
    bool keyTest = false;   // tests if key exists
    node *pn = static_cast<node *> (mapping->getPointer(id, &keyTest));

    if (!keyTest)
        return 1;

    int nLoc = getPos(pn);

    data[nLoc].key = key;

    bool percDown;
    percDown = ((nLoc*2 <= size ) && (data[nLoc].key > data[nLoc*2].key)) || \
               ((nLoc*2+1 <= size) && (data[nLoc].key > data[nLoc*2+1].key)) || \
               (nLoc == 1);
    
    // checks heap order property violation, percolates up or down if necessary
    if (percDown)
        percolateDown(nLoc);
    else if (data[nLoc].key < data[nLoc/2].key)
        percolateUp(nLoc);

    return 0;
}

// Removes top node, overwrites data and percolates down to place.
int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (size == 0)
        return 1;

    if (pId)
        *pId = data[1].id;
    if (pKey)
        *pKey = data[1].key;
    if (ppData)
        *(static_cast<void **> (ppData)) = data[1].pData;

    // removes string from hashtable
    mapping->remove(data[1].id);

    // overwrites first item with last item and percolates down to adjust.
    data[1] = data[size];
    size--;
    percolateDown(1);
    return 0;
}

// 
int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool exists = false;
    node *pn = static_cast<node *> (mapping->getPointer(id, &exists));

    if (!exists)
        return 1;

    int nLoc = getPos(pn);  // tracks node location

    if (pKey)
        *pKey = data[nLoc].key;
    if (ppData)
        *(static_cast<void **> (ppData)) = data[nLoc].pData;

    // remove id from hashtable
    mapping->remove(id);

    // overwrite nLoc with last element, set new pointer,
    data[nLoc] = data[size];
    mapping->setPointer(data[nLoc].id, &data[nLoc]);
    size--;

    // checks heap order property, percolates if necessary
    bool percDown;
    percDown = ((nLoc*2 <= size ) && (data[nLoc].key > data[nLoc*2].key)) || \
               ((nLoc*2+1 <= size) && (data[nLoc].key > data[nLoc*2+1].key)) || \
               (nLoc == 1);
    if (percDown)
        percolateDown(nLoc);
    else if (data[nLoc].key < data[nLoc/2].key)
        percolateUp(nLoc);

    return 0;

}

// Percolate up: starts with value at bottom of tree. Swaps with higher values to move to the top.
void heap::percolateUp(int posCur) {
    int pos2 = posCur;
    node temp = data[posCur];

    while ( pos2 > 1 && temp.key < data[pos2/2].key) {
        data[pos2] = data[pos2/2];
        mapping->setPointer(data[pos2].id, &data[pos2]);
        pos2 /= 2;
    }

    data[pos2] = temp;
    mapping->setPointer(data[pos2].id, &data[pos2]);
}

// Percolate down. Source: Textbook [Data Structures and Algorithm Analysis in C++, Third Edition]
void heap::percolateDown(int posCur) {
    int child;
    int pos2 = posCur;
    node temp = data[posCur];

    while ( pos2 * 2 <= size) {
        child = pos2 * 2;
        if (child != size && data[child+1].key < data[child].key)
            child++;
        if (data[child].key < temp.key) {
            data[pos2] = data[child];
            mapping->setPointer(data[pos2].id, &data[pos2]);
        }
        else
            break;
        pos2 = child;
    }
    data[pos2] = temp;
    mapping->setPointer(data[pos2].id, &data[pos2]);
}

// Retrieves the position of a particular node.
int heap::getPos(node *pn) {
    int pos = pn - &data[0];
    return pos;
}