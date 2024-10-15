#include <iostream>
#include <vector>
using namespace std;

class HashTable {
private:
    vector<int> table;  // Hash table storing the keys
    int tableSize;      // Current size of the hash table
    int numElements;    // Number of elements currently in the table
    double loadFactor;  // Load factor threshold

    // Helper function to check if a number is prime
    bool isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    // Find the next prime number greater than or equal to n
    int nextPrime(int n) {
        while (!isPrime(n)) n++;
        return n;
    }

    // Rehash the table when resizing
    void rehash() {
        int oldSize = tableSize;
        vector<int> oldTable = table;

        tableSize = nextPrime(2 * oldSize);
        table.assign(tableSize, -1); // Reset table to new size
        numElements = 0;

        for (int i = 0; i < oldSize; i++) {
            if (oldTable[i] != -1) {
                insert(oldTable[i]);
            }
        }
    }

    // Hash function
    int hashFunction(int key) {
        return key % tableSize;
    }

public:
    // Constructor
    HashTable(int size) {
        tableSize = nextPrime(size);
        table.assign(tableSize, -1);
        numElements = 0;
        loadFactor = 0.8;
    }

    // Insert function with quadratic probing
    void insert(int key) {
        if (search(key) != -1) {
            cout << "Duplicate key insertion is not allowed" << endl;
            return;
        }

        if (numElements >= loadFactor * tableSize) {
            rehash();
        }

        int index = hashFunction(key);
        int i = 0;
        while (i < (tableSize + 1) / 2) {
            int probeIndex = (index + i * i) % tableSize;
            if (table[probeIndex] == -1) {
                table[probeIndex] = key;
                numElements++;
                return;
            }
            i++;
        }
        cout << "Max probing limit reached!" << endl;
    }

    // Remove function with quadratic probing
    void remove(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (i < (tableSize + 1) / 2) {
            int probeIndex = (index + i * i) % tableSize;
            if (table[probeIndex] == key) {
                table[probeIndex] = -1;
                numElements--;
                return;
            }
            if (table[probeIndex] == -1) {
                cout << "Element not found" << endl;
                return;
            }
            i++;
        }
        cout << "Element not found" << endl;
    }

    // Search function with quadratic probing
    int search(int key) {
        int index = hashFunction(key);
        int i = 0;
        while (i < (tableSize + 1) / 2) {
            int probeIndex = (index + i * i) % tableSize;
            if (table[probeIndex] == key) {
                return probeIndex;
            }
            if (table[probeIndex] == -1) {
                return -1;
            }
            i++;
        }
        return -1;
    }

    // Print the current state of the table
    void printTable() {
        for (int i = 0; i < tableSize; i++) {
            if (table[i] == -1) {
                cout << "- ";
            } else {
                cout << table[i] << " ";
            }
        }
        cout << endl;
    }
};
