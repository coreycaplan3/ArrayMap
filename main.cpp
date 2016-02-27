#include <iostream>
#include "ArrayMap.h"

using namespace std;

int main(int argc, char **argv) {
    ArrayMap *arrayMap = new ArrayMap();
    arrayMap->put("hello", 5);
    arrayMap->put("helol", 10);
    arrayMap->put("Corey", 20);
    arrayMap->put("dog", 25);
    arrayMap->put("tac", 30);
    arrayMap->put("trac", 35);
    arrayMap->put("mak", 45);
    arrayMap->put("tackle", 50);
    arrayMap->put("hack", 55);

    cout << "Successfully put all of words!" << endl;

    cout << "Result: " << arrayMap->get("hello") << endl;
    cout << "Result: " << arrayMap->get("helol") << endl;
    cout << "Should not be found: " << arrayMap->get("cat") << endl;
    cout << "Result: " << arrayMap->get("dog") << endl;
    cout << "Result: " << arrayMap->get("tac") << endl;
    cout << "Result: " << arrayMap->get("trac") << endl;
    cout << "Result: " << arrayMap->get("mak") << endl;
    cout << "Result: " << arrayMap->get("tackle") << endl;
    cout << "Result: " << arrayMap->get("hack") << endl;

    cout << "Successfullly got all words!" << endl;

    cout << "Get: " << arrayMap->get("helol") << endl;
    cout << "Remove: " << arrayMap->remove("helol") << endl;
    cout << "After remove: " << arrayMap->get("helol") << endl;

//    arrayMap->printContent();
    return 0;
}