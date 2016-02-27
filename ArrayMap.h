//
// Created by Corey Caplan on 2/22/16.
//

#ifndef ARRAYMAP_ARRAYMAP_H
#define ARRAYMAP_ARRAYMAP_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Item {
    int value;
    string key;
};

class ArrayMap {

public:

    /**
     * Default constructor that initializes the ArrayMap to be of size one
     */
    ArrayMap();

    /**
     * Puts the item into the map for the given key
     */
    void put(string key, int item);

    /**
     * Gets the item for the given key
     */
    int get(string key);

    /**
     * Removes the item for the given key and returns the value that was removed.
     */
    int remove(string key);

    void printContent();

    ~ArrayMap();

private:

    /**
     * Binary searches the #hashedValues array to find the index of where the hashedValue is entered.
     */
    int binarySearchInsert(int hashedValue);

    int linearSearchGet(int hashedValue);

    int binarySearchGet(int hashedValue);

    int spaceLeft;
    int arraySize;
    int *hashedValues;
    Item **arrayMap;

    /**
     * @param index The location of the shift
     */
    void shiftRemoval(int index);

    /**
     * @param index The location of the shift
     */
    void shiftInsert(int index);

    /**
     * Hashes a string (key) to an integer value.
     */
    int hash(string key);

    /**
     * Reallocates the array of hashes and items to a larger array.
     */
    void reallocate();

    /**
     * Deallocates the array of hashes and items to a smaller array.
     */
    void deallocate();
};


#endif //ARRAYMAP_ARRAYMAP_H
