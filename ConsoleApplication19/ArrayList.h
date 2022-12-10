#include <iostream>
#include <string>
#include <cstring>
#pragma once

using namespace std;

// Custom exception in case of error at getting an element
class ArrayListIndexOutBound :public std::exception {
private:
    std::string error = "";
    long long index = 0;
public:
    ArrayListIndexOutBound();
    ArrayListIndexOutBound(int index);
    char* what();
};
// We created a template to generate a dynamic linked list as an array
// We added Heapsort and Quicksort with the posibility to sort with a custom function
template <typename T> struct ArrayList {
public:
    // We created an iterator for the linked list
    struct ArrayListI {
        T value;
        ArrayListI* next = NULL;
        ArrayListI* prev = NULL;
        T& operator =(const T& b);
        T& operator =(const ArrayListI& b);
        static ArrayListI* newArrayListI(T value) {
            ArrayListI* n = new ArrayListI;
            if (n == NULL)
                return NULL;
            n->value = value;
            n->next = NULL;
            n->prev = NULL;
            return n;
        }
    };
    // Retreive the origin of the linked list
    ArrayList<T>::ArrayListI* getOrigin();
    // Retreive the end of the linked list
    ArrayListI* getLast();
    // Returns the iterator in the I position
    ArrayListI* getIterator(long long i);
    // Set a element in the I position and return the previous Element
    T set(long long i, T value);
    // Get the element in the I position
    T get(long long i);
    // Add element at the end of the list
    bool add(T value);
    // Add element at the end of the list
    bool push_back(T value);
    // Add element in front of the list
    bool push_front(T value);
    // Delete an element from the list and return the value in the index
    T erase(long long int i);
    // Overload the operator [] to get the elements as a list
    T operator[](long long i);
    // Returns the size of the list
    long long getSize();
    // A utility function to swap two index in the list
    void swap(long long i, long long j);
    // A utility function to swap two iterators in the list
    void swap(ArrayListI* a, ArrayListI* b);

    // Basic quicksort with default sorting
    bool quicksort();
    // Quicksort with custom sorting
    bool quicksort(bool (*callback)(T value1, T value2));
    // Basic heapsort with default sorting
    bool heapsort();
    // Heapsort with custom sorting
    bool heapsort(bool (*callback)(T value1, T value2));
    // Clear the list
    void clear();
    // Search and return matches
    ArrayList<T>* filter(T filter, bool (*callback)(T value, T filter));
    void toList(T* values, long long vsize);
    void toList(ArrayList<T>* L);
    T* toArray();
    ArrayList<T>* clone();
    static ArrayList<T>* arrayToList(T* values, long long vsize) {
        ArrayList<T>* conv = new ArrayList<T>;
        conv->toList(values, vsize);
        return conv;
    }
private:
    // First position in the list
    ArrayListI* origin = NULL;
    // Size of the list
    long long size = 0;
    // Last position in the list
    ArrayListI* last = NULL;
    // Main iterator for searching elements
    ArrayListI* it = NULL;
    // Last index retreived in the iterator
    long long itIndex = 0;

    /* This function takes last element as pivot, places
    the pivot element at its correct position in sorted
    list, and places all smaller (smaller than pivot)
    to left of pivot and all greater elements to right
    of pivot */
    long long partition(long long low, long long high, bool (*callback)(T value1, T value2));
    /* The main function that implements QuickSort
    low --> Starting index,
    high --> Ending index
    callback --> custom function for sorting
    */
    void quickSort(long low, long high, bool (*callback)(T value1, T value2));
    // To heapify a subtree rooted with node i
    // which is an index in the list.
    // n is size of heap
    void heapify(long long N, long long i, bool (*callback)(T value1, T value2));
    // Default function for sorting
    bool sort_default(T value1, T value2);
};