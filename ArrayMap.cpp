//
// Created by Corey Caplan on 2/22/16.
//

#include "ArrayMap.h"

ArrayMap::ArrayMap() {
    arraySize = 1;
    spaceLeft = arraySize;
    hashedValues = new int[arraySize];
    arrayMap = new Item *[arraySize];

    for (int i = 0; i < arraySize; i++) {
        hashedValues[i] = -1;
    }
    for (int i = 0; i < arraySize; i++) {
        arrayMap[i] = NULL;
    }
}

void ArrayMap::put(string key, int item) {
    if (spaceLeft == 0) {
        reallocate();
    }
    spaceLeft--;
    int hashedValue = hash(key);
    int indexForHash = binarySearchInsert(hashedValue);

    Item *data = new Item();
    data->value = item;
    data->key = key;
    if (arrayMap[indexForHash] != NULL) {
        if (arrayMap[indexForHash]->key == key) {
            //If there isn't a collision, just insert it.
            arrayMap[indexForHash] = data;
            hashedValues[indexForHash] = hashedValue;
        } else {
            //If there is a collision shift everything over to the right and insert it at this spot.ß
            shiftInsert(indexForHash);
            arrayMap[indexForHash] = data;
            hashedValues[indexForHash] = hashedValue;
        }
    } else {
        arrayMap[indexForHash] = data;
        hashedValues[indexForHash] = hashedValue;
    }
}

int ArrayMap::get(string key) {
    int hashedValue = hash(key);
    int indexForHash = binarySearchGet(hashedValue);
    if (indexForHash == -1) {
        //The search doesn't find the hashed value
        return -1;
    }

    Item *item = arrayMap[indexForHash];
    if (item->key == key) {
        return item->value;
    }

    //Assume there is a collision
    int indexLow = indexForHash;
    int indexHigh = indexForHash;
    while (indexLow >= 0 || indexHigh < arraySize) {
        //Walk below and above the index until we find the value for the given key
        if (--indexLow >= 0) {
            if (arrayMap[indexLow] != NULL) {
                if (arrayMap[indexLow]->key == key) {
                    return arrayMap[indexLow]->value;
                }
            }
        }
        if (++indexHigh < arraySize) {
            if (arrayMap[indexHigh] != NULL) {
                if (arrayMap[indexHigh]->key == key) {
                    return arrayMap[indexHigh]->value;
                }
            }
        }
    }
    return -1;
}

int ArrayMap::remove(string key) {
    int hashedValue = hash(key);
    int indexForHash = linearSearchGet(hashedValue);
    if (indexForHash == -1) {
        //The value is not found
        return -1;
    }

    //Assume there is a collision
    int returnValue = -1;
    int indexForRemoval = indexForHash;
    int indexLow = indexForHash;
    int indexHigh = indexForHash;
    while (--indexLow >= 0 || ++indexHigh < arraySize) {
        //Walk below and above the index until we find the value for the given key
        if (indexLow >= 0) {
            if (arrayMap[indexLow] != NULL) {
                if (arrayMap[indexLow]->key == key) {
                    returnValue = arrayMap[indexLow]->value;
                    indexForRemoval = indexLow;
                }
            }
        }
        if (indexHigh < arraySize) {
            if (arrayMap[indexHigh] != NULL) {
                if (arrayMap[indexHigh]->key == key) {
                    returnValue = arrayMap[indexHigh]->value;
                    indexForRemoval = indexHigh;
                }
            }
        }
    }

    if (returnValue > 0) {
        shiftRemoval(indexForRemoval);
        deallocate();
    }
    return returnValue;
}

int ArrayMap::hash(string key) {
    int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += key[i];
    }
    return hash;
}

int ArrayMap::linearSearchGet(int hashedValue) {
    for (int i = 0; i < arraySize; i++) {
        if (hashedValues[i] == hashedValue) {
            return i;
        }
    }
    return -1;
}

int ArrayMap::binarySearchGet(int hashedValue) {
    int mid;
    int low = 0;
    int high = arraySize - 1;
    while (low < high) {
        mid = (low + high) >> 1;
        if (hashedValues[mid] == hashedValue) {
            return mid;
        }
        else if (hashedValues[mid] > hashedValue) {
            high = mid - 1;
        } else if (hashedValues[mid] < hashedValue) {
            low = mid + 1;
        }
    }
    return -1;
}

int ArrayMap::binarySearchInsert(int hashedValue) {
    int low = 0;
    int high = arraySize - 1;
    int mid = -1;

    while (low <= high) {
        mid = (low + high) / 2;
        if (hashedValues[mid] == hashedValue) {
            return mid;
        } else if (hashedValues[mid] > hashedValue) {
            high = mid - 1;
        } else if (hashedValues[mid] < hashedValue) {
            low = mid + 1;
        }
    }
    return mid;
}

void ArrayMap::shiftInsert(int index) {
    //Move all the elements after the index to the right by one
    //Assume we have enough room and allocate was called (if necessary)
    int lastIndex = arraySize - 2;
    for (int i = lastIndex; i >= index; i--) {
        arrayMap[i + 1] = arrayMap[i];
        hashedValues[i + 1] = hashedValues[i];
    }
}

void ArrayMap::shiftRemoval(int index) {
    //Move all the elements starting at the index to the left by one
    int lastIndex = arraySize - 1;
    for (int i = index; i < lastIndex; i++) {
        hashedValues[i] = hashedValues[i + 1];
        arrayMap[i] = arrayMap[i + 1];
    }
}

void ArrayMap::reallocate() {
    spaceLeft += 1;
    arraySize += 1;
    int oldArraySize = arraySize - 1;

    Item **temp = new Item *[oldArraySize];
    for (int i = 0; i < oldArraySize; i++) {
        temp[i] = arrayMap[i];
    }
    arrayMap = new Item *[arraySize];
    for (int i = 0; i < oldArraySize; i++) {
        arrayMap[i] = temp[i];
    }
    for (int i = oldArraySize; i < arraySize; i++) {
        arrayMap[i] = NULL;
    }

    int *tempHash = new int[oldArraySize];
    for (int i = 0; i < oldArraySize; i++) {
        tempHash[i] = hashedValues[i];
    }

    hashedValues = new int[arraySize];
    for (int i = 0; i < oldArraySize; i++) {
        hashedValues[i] = tempHash[i];
    }

    int largestNum = hashedValues[(oldArraySize) - 1];
    for (int i = oldArraySize; i < arraySize; i++) {
        hashedValues[i] = largestNum + 1;
    }
}

void ArrayMap::deallocate() {
    spaceLeft -= 1;
    arraySize -= 1;

    Item **tempItems = new Item *[arraySize];
    for (int i = 0; i < arraySize; i++) {
        tempItems[i] = arrayMap[i];
    }
    arrayMap = new Item *[arraySize];
    for (int i = 0; i < arraySize; i++) {
        arrayMap[i] = tempItems[i];
    }

    int *tempHashes = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        tempHashes[i] = hashedValues[i];
    }
    hashedValues = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        hashedValues[i] = tempHashes[i];
    }
}

void ArrayMap::printContent() {
    cout << "Hashed Values:" << endl;
    for (int i = 0; i < arraySize; i++) {
        cout << "Index: " << i << " Hash: " << hashedValues[i] << endl;
    }

    cout << "Items: " << endl;
    for (int i = 0; i < arraySize; i++) {
        if (arrayMap[i] == NULL) {
            cout << "Index: " << i << " content NULL" << endl;
        } else {
            cout << "Index: " << i << " (Key: " << arrayMap[i]->key << ") (Value: " << arrayMap[i]->value << ")" <<
            endl;
        }
    }
}

ArrayMap::~ArrayMap() {
    delete[](hashedValues);
    delete[](arrayMap);
}
