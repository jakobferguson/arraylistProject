//
// Created by Jakob Ferguson on 3/5/23.
//
#ifndef ARRAYLIST_HPP
#define ARRAYLIST_HPP

#include <iostream>

/*
   * ----- Auxiliary Functions -----
   */

// Purpose: Increases size of storage array
// Postconditions: a new array of size m_max*2 is allocated,
//     and m_data is copied to it.
//     m_max is set to the size of this new storage array
template <typename T>
void ArrayList<T>::grow(){
    T *temp = new T[2*(this->m_size)];
    for(int i=0; i<m_size; i++) {
        temp[i] = this->m_data[i];
    }
    delete[] m_data;
    this->m_data = temp;
    this->m_max*=2;
}


// Purpose: Decreases size of storage array
// Postconditions: a new array of size m_max/2 is allocated,
//     and m_data is copied to it.
//     m_max is set to the size of this new storage array
template <typename T>
void ArrayList<T>::shrink() {
    //std::cout << (this->m_size)/2 << std::endl;
    T *temp = new T[(this->m_max)/2];
    for(int i=0; i<m_size; i++) {
        temp[i] = this->m_data[i];
    }
    delete[] m_data;
    this->m_data = temp;
    temp = NULL;
    this->m_max/=2;
}


/*
 * ---- Constructors ---
 */

// Purpose: Parameterized Constructor
// Parameters:  s : the requested size of the list
//              x : the initial values in the list
// Postconditions:  the list is constructed as a list of 's' copies of 'x'
template <typename T>
ArrayList<T>::ArrayList(int s, const T& x) {
    m_data = new T[s*2];
    m_size = s;
    m_max = s*2;
    for(int i=0; i<m_size;i++) {
        m_data[i] = x;
    }
}


/*
 * ---- Big 3 Member Functions ---
 */

// Purpose: Destructor
// Postconditions: current size and maximum size set to 0,
//                 data deallocated and set to NULL
template <typename T>
ArrayList<T>::~ArrayList() {
    m_max = 0;
    m_size = 0;
    delete[] m_data;
    m_data = NULL;
}

// Purpose: Operator=, performs a deep copy of 'rhs' into 'this' ArrayList
// Parameters: rhs : ArrayList to be copied
// Returns: *this
// Postconditions: rhs == this
template <typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& rhs) {
    delete []m_data;
    m_data = new T[rhs.m_max];
    m_max = rhs.m_max;
    for(int i=0;i<rhs.m_size;i++){
        m_data[i] = rhs.m_data[i];
    }
    m_size = rhs.m_size;
    return *this;
}
// Purpose: Copy Constructor
// Parameters: cpy = ArrayList to be copied
// Postconditions: current size, maximum size, and elements same as cpy
template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T>& cpy) {
    this->m_data = NULL;
    m_max=m_size=0;
    *this = cpy;
}


/*
 * ----- Basic Accessor Operations -----
 */

// Purpose: Accessor function for the number of elements in the list
// Returns: number of elements in the list
template <typename T>
int ArrayList<T>::size() const {
    return m_size;
}

// Purpose: Accessor function for the first element of the list
// Returns: the first element in the list
template <typename T>
const T& ArrayList<T>::first() const {
    if(m_size==0){
        std::cout << "!!! ERROR : ARRAYLIST.first() !!! (List is empty)" << std::endl;
    }
    return m_data[1];
}

// Purpose: return a read-and-write reference to the element at
// the specified position
// Parameters: i is 0-based index into the ArrayList
// Returns: the element at position i in the ArrayList
template <typename T>
T& ArrayList<T>::operator[](int i) {
    if(i>(m_size-1)){
        std::cout << "!!! ERROR : ARRAYLIST.operator[] !!! (index out of bounds)"<< std::endl;
    }
    return this->m_data[i];
}

// Purpose: return a read-only reference to the element at
// the specified position
// Parameters: i is 0-based index into the ArrayList
// Returns: the element at position i in the ArrayList
template <typename T>
const T& ArrayList<T>::operator[](int i) const {
    if(i>(m_size-1)){
        std::cout << "!!! ERROR : ARRAYLIST.operator[] !!! (index out of bounds)"<< std::endl;
    }
    return this->m_data[i];
}

// Purpose: finds an element in the ArrayList
// Parameters: 'x' is value to be found in the ArrayList
// Returns: the position of the first occurrance of 'x' in the list,
//          or -1  if 'x' is not found.
template <typename T>
int ArrayList<T>::search(const T& x) const {
    for(int i=0;i<m_size;i++) {
        if(x == m_data[i]) {
            return i;
        }
    }
    return -1;
}


/*
 * ----- Basic Mutator Operations -----
 */
// Purpose: Clears the ArrayList
// Postconditions: storage array is deallocated,
//                 and a new storage array of size 4 is allocated.
//                 max size is set to 4,
//                 list size is set to 0.
//                 ( same as default constructor )
template <typename T>
void ArrayList<T>::clear() {
    delete[] m_data;
    m_data = new T[4];
    m_max = 4;
    m_size = 0;

}

// Purpose: puts the value x at the end of an ArrayList
// Parameters: x is value to be added to ArrayList
// Postconditions: current size is incremented by 1
//     If max size is reached, the storage wrray is grown.
template <typename T>
void ArrayList<T>::insert_back(const T& x) {
    if(m_size==m_max) {
        this->grow();
    }
    m_data[m_size] = x;
    m_size++;

}

// Purpose: puts the value x at the position i in the  ArrayList
// Parameters: x is value to be added to ArrayList
//             i is the position to insert x at
// Postconditions: current size is incremented by 1
//     If max size is reached, the storage array is grown().
template <typename T>
void ArrayList<T>::insert(const T& x, int i) {
    if(i>(m_size-1)){
        std::cout << "!!! ERROR : ARRAYLIST.insert() !!! (index out of bounds)"<< std::endl;
    }
    if(m_size==m_max) {
        this->grow();
    }
    for(int k=m_size; k > i; k--){
        m_data[k]=m_data[k-1];
    }
    m_data[i] = x;
    m_size++;
}


// Purpose: Removes the element at index i in the array
// Parameters: i, the index of the element to remove
// Postconditions: if the size of the list is greater than 0
//     size is decremented by one.
//     if the size of the list less than 1/4 the max size,
//     the storage array is shrunk.
template <typename T>
void ArrayList<T>::remove(int i) {
    if(i>(m_size-1)){
        std::cout << "!!! ERROR : ARRAYLIST.remove() !!! (index out of bounds)"<< std::endl;
    }
    if(i != (m_size-1)) {
        for (int j = i; j < m_size - 1; j++) {
            m_data[j] = m_data[j + 1];
        }
    }
    m_size--;
    if(m_size<=(m_max/4)){
        //std::cout << m_size << " " << m_max << std::endl;
        this->shrink();
    }
}


/*
 * ----- Complex Mutator Operations -----
 */

// Purpose: swaps two elements of the array
// Parameters: i, k, two positions on the Arraylist
// Postconditions: the elements at positions i and k swap positions
template <typename T>
void ArrayList<T>::swap(int i, int k) {
    if((i>(m_size-1)) ||(k>(m_size-1))){
        std::cout << "!!! ERROR : ARRAYLIST.swap() !!! (index out of bounds)"<< std::endl;
    }
    T temp = m_data[i];
    m_data[i] = m_data[k];
    m_data[k] = temp;
}

// Purpose: appends two lists
// Parameters: alist, a list to appended to the end of 'this' list
// Postconditions: current size is incremented by size of alist
//     the elements of alist are appended to the elements of 'this'
template <typename T>
void ArrayList<T>::append(const ArrayList<T>& alist) {
    while((m_size+alist.m_size)>m_max) {
        this->grow();
    }
    int j=0;
    for(int i=m_size;i<(m_size+alist.m_size);i++) {
        m_data[i] = alist.m_data[j];
        j++;
    }
    m_size+=alist.m_size;
}

// Purpose: Reverses an ArrayList
// Postconditions: the elements in the list are now reversed.
template <typename T>
void ArrayList<T>::reverse(){
    T *tempA = new T[this->m_size];
    for(int i=0;i<m_size;i++){
        tempA[i] = m_data[i];
    }
    for(int i=0;i<m_size;i++){
        m_data[i] = tempA[((m_size-1)-i)];
    }
    delete[] tempA;
}


#endif