#include "ArrayList.h"
#include "Persona.h"
#include "Calificaciones.h"

template struct ArrayList<PERSONA*>;
template struct ArrayList<CALIFICACIONES*>;
template struct ArrayList<char>;

ArrayListIndexOutBound::ArrayListIndexOutBound() {
    this->error.append("Array index out of bound");
}
ArrayListIndexOutBound::ArrayListIndexOutBound(int index) {
    this->error.append("Array index {").append(std::to_string(index)).append("} out of bound");
}
char* ArrayListIndexOutBound::what() {
    return (char*)this->error.c_str();
}

template <typename T>
typename T& ArrayList<T>::ArrayListI::operator =(const T& b) {
    this->value = b;
    return this->value;
}
template <typename T>
typename T& ArrayList<T>::ArrayListI::operator =(const ArrayListI &b) {
    this->value = b.value;
    return this->value;
}

// Retreive the origin of the linked list
template <typename T>
typename ArrayList<T>::ArrayListI* ArrayList<T>::getOrigin() {
    return origin;
}
// Retreive the end of the linked list
template <typename T>
typename ArrayList<T>::ArrayListI* ArrayList<T>::getLast() {
    return last;
}
// Returns the iterator in the I position
template <typename T>
typename ArrayList<T>::ArrayListI* ArrayList<T>::getIterator(long long i) {
    if (i >= size)
        throw ArrayListIndexOutBound(i);
    int pointer =
        abs(0 - i) > abs(size - i) ? (abs(size - i) > abs(itIndex - i) ? 3 : 2) : (abs(0 - i) > abs(itIndex - i) ? 3 : 1);
    long long count = pointer == 1 ? 0 : (pointer == 2 ? size - 1 : itIndex);
    ArrayListI* iterator = pointer == 1 ? origin : (pointer == 2 ? last : it);
    //    cout << (pointer == (byte)1 ? "origin" : (pointer == (byte)2 ? "last" : "itIndex")) << endl;
    while (count < i && iterator != NULL) {
        count++;
        iterator = iterator->next;
    }
    while (count > i && iterator != NULL) {
        count--;
        iterator = iterator->prev;
    }
    it = iterator;
    itIndex = count;
    return iterator;
}
// Set a element in the I position and return the previous Element
template <typename T>
T ArrayList<T>::set(long long i, T value) {
    ArrayListI* iterator = getIterator(i);
    T val = iterator->value;
    iterator->value = value;
    return val;
}
// Get the element in the I position
template <typename T>
T ArrayList<T>::get(long long i) {
    ArrayListI* iterator = getIterator(i);
    return iterator->value;
}
// Add element at the end of the list
template <typename T>
bool ArrayList<T>::add(T value) {
    ArrayListI* n =
        ArrayListI::newArrayListI(value);
    if (n == NULL)
        return false;
    origin = origin == NULL ? n : origin;
    if (last != NULL)
        last->next = n;
    n->prev = last;
    last = n;
    size++;
    itIndex = it == NULL ? 0 : itIndex;
    it = it == NULL ? origin : it;
    return true;
}
// Add element at the end of the list
template <typename T>
bool ArrayList<T>::push_back(T value) {
    return add(value);
}
// Add element in front of the list
template <typename T>
bool ArrayList<T>::push_front(T value) {
    ArrayListI* n =
        ArrayListI::newArrayListI(value);
    if (n == NULL)
        return false;
    last = last == NULL ? n : last;
    if (origin != NULL)
        origin->prev = n;
    n->next = origin;
    origin = n;
    size++;
    itIndex = it == NULL ? 0 : itIndex;
    it = it == NULL ? origin : it;
    return true;
}
// Delete an element from the list and return the value in the index
template <typename T>
T ArrayList<T>::erase(long long int i) {
    ArrayListI* iterator = getIterator(i);
    T value = iterator->value;
    if (iterator != NULL) {
        ArrayListI* next = iterator->next;
        ArrayListI* prev = iterator->prev;
        if (prev != NULL)
            prev->next = iterator->next;
        if (next != NULL)
            next->prev = iterator->prev;
        if (iterator == origin)
            origin = next;
        if (iterator == last)
            last = prev;
        itIndex = iterator == it ? (itIndex - 1 < 0 ? 0 : itIndex - 1) : itIndex;
        it = it == iterator ? (prev == NULL ? origin : prev) : it;
        delete iterator;
        size--;
    }
    return value;
}
// Overload the operator [] to get the elements as a list
template <typename T>
T ArrayList<T>::operator[](long long i) {
    return this->get(i);
}
// Returns the size of the list
template <typename T>
long long ArrayList<T>::getSize() {
    return size;
}
// A utility function to swap two index in the list
template <typename T>
void ArrayList<T>::swap(long long i, long long j) {
    swap(getIterator(i), getIterator(j));
}
// A utility function to swap two iterators in the list
template <typename T>
void ArrayList<T>::swap(ArrayList<T>::ArrayListI* a, ArrayList<T>::ArrayListI* b) {
    T t = a->value;
    a->value = b->value;
    b->value = t;
}

// Basic quicksort with default sorting
template <typename T>
bool ArrayList<T>::quicksort() {
    quickSort(0, size - 1, NULL);
    return true;
}
// Quicksort with custom sorting
template <typename T>
bool ArrayList<T>::quicksort(bool (*callback)(T value1, T value2)) {
    quickSort(0, size - 1, callback);
    return true;
}
// Basic heapsort with default sorting
template <typename T>
bool ArrayList<T>::heapsort() {
    return heapsort(NULL);
}
// Heapsort with custom sorting
template <typename T>
bool ArrayList<T>::heapsort(bool (*callback)(T value1, T value2)) {
    // Build heap (rearrange array)
    for (long long i = size / 2 - 1; i >= 0; i--)
        heapify(size, i, callback);
    // One by one extract an element
    // from heap
    for (long long i = size - 1; i > 0; i--) {
        // Move current root to end
        swap(origin, getIterator(i));
        // call max heapify on the reduced heap
        heapify(i, 0, callback);
    }
    return true;
}
// Clear the list
template <typename T>
void ArrayList<T>::clear() {
    it = origin;
    while (it != NULL) {
        origin = origin->next;
        delete it;
        it = origin;
    }
    size = 0;
    itIndex = 0;
    last = NULL;
}
// Search and return matches
template <typename T>
ArrayList<T>* ArrayList<T>::filter(T filter, bool (*callback)(T value, T filter)) {
    if (callback == NULL || size < 1 || origin == NULL || last == NULL)
        return NULL;
    ArrayList<T>* ret = new ArrayList<T>;
    ArrayListI* iterator = origin, * iteratorE = last;
    while (iterator != NULL) {
        if (callback(iterator->value, filter))
            ret->add(iterator->value);
        if (iterator != iteratorE && callback(iteratorE->value, filter))
            ret->add(iteratorE->value);
        iteratorE = iteratorE->prev;
        iterator = iterator->next;
        if (iterator->prev == iteratorE || iterator->prev == iteratorE->next)
            break;
    }
    if (ret->size < 1) {
        delete ret;
        ret = NULL;
    }
    return ret;
}
template <typename T>
void ArrayList<T>::toList(T* values, long long vsize) {
    for (int i = 0; i < vsize; i++)
        add(values[i]);
}
template <typename T>
void ArrayList<T>::toList(ArrayList<T>* L) {
    ArrayListI *aux = L->getOrigin();
    while (aux != NULL) {
        add(aux->value);
        aux = aux->next;
    }
}
template <typename T>
T* ArrayList<T>::toArray() {
    T* arr = new T[getSize()];
    ArrayListI* iterator = origin;
    long long i = 0;
    while (iterator != NULL) {
        arr[i] = iterator->value;
        iterator = iterator->next;
        i++;
    }
    return arr;
}

template <typename T>
long long ArrayList<T>::partition(long long low, long long high, bool (*callback)(T value1, T value2)) {
    //T pivot = get(high); // pivot
    ArrayListI* pivoti = getIterator(high);
    long long i
        = (low
            - 1); // Index of smaller element and indicates
    // the right position of pivot found so far

    for (long long j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        ArrayListI* ji = getIterator(j);
        if ((callback != NULL && callback(ji->value, pivoti->value)) or (callback == NULL && sort_default(ji->value, pivoti->value))) {
            i++; // increment index of smaller element
            swap(getIterator(i), ji);
        }
    }
    swap(getIterator(i + 1), pivoti);
    return (i + 1);
}
/* The main function that implements QuickSort
low --> Starting index,
high --> Ending index
callback --> custom function for sorting
*/
template <typename T>
void ArrayList<T>::quickSort(long low, long high, bool (*callback)(T value1, T value2)) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
        at right place */
        long long pi = partition(low, high, callback);

        // Separately sort elements before
        // partition and after partition
        quickSort(low, pi - 1, callback);
        quickSort(pi + 1, high, callback);
    }
}
// To heapify a subtree rooted with node i
// which is an index in the list.
// n is size of heap
template <typename T>
void ArrayList<T>::heapify(long long N, long long i, bool (*callback)(T value1, T value2)) {
    // Initialize largest as root
    long long largest = i;
    // left = 2*i + 1
    long long l = 2 * i + 1;
    // right = 2*i + 2
    long long r = 2 * i + 2;
    // If left child is larger than root
    ArrayListI* li = l < N ? getIterator(l) : NULL, * ri = r < N ? getIterator(r) : NULL, * largesti = getIterator(largest);
    if (l < N && ((callback != NULL && callback(largesti->value, li->value)) or (callback == NULL && sort_default(largesti->value, li->value)))) {
        largest = l;
        largesti = li;
    }
    // If right child is larger than largest
    // so far
    if (r < N && ((callback != NULL && callback(largesti->value, ri->value)) or (callback == NULL && sort_default(largesti->value, ri->value)))) {
        largest = r;
        largesti = ri;
    }
    // If largest is not root
    if (largest != i) {
        swap(getIterator(i), largesti);
        // Recursively heapify the affected
        // sub-tree
        heapify(N, largest, callback);
    }
}
// Default function for sorting
template <typename T>
bool ArrayList<T>::sort_default(T value1, T value2) {
    return value1 > value2;
}
template <typename T>
ArrayList<T>* ArrayList<T>::clone(){
    if (size < 1)
        return NULL;
    ArrayListI* aux = origin;
    ArrayList<T> *n = new ArrayList<T>;
    while (aux != NULL) {
        n->add(aux->value);
        aux = aux->next;
    }
    return n;
}
