//
// Created by andres on 2023-03-28.
//

#ifndef P2_NORMALHEAP_H
#define P2_NORMALHEAP_H

#include "algorithm"
#include "vector"
using namespace std;

template <typename T>
class NormalHeap {
private:
    std::vector<T> data; 
    //move an element up to the appropriate position
    void perlocateUp(int idx); 
    //move an element down to the appropriate position
    void perlocateDown(int idx); 
public:
    // constructor
    NormalHeap(); 
    // function to insert a new element in the heap
    void insert(const T& t); 
    // function to return the minimum element in the heap
    T getMin(); 
    // function to delete the minimum element in the heap
    void deleteMin(); 
    // function to check whether the heap is empty or not
    bool isEmpty(){return data.size()==1;} 
};

template<typename T>
void NormalHeap<T>::insert(const T &t) {
    // add the new element to the end of the vector
    data.push_back(t); 
    // move the element up to the appropriate position
    perlocateUp(data.size()-1); 
}

template<typename T>
void NormalHeap<T>::perlocateUp(int idx) {
    int i;
    // save the element that needs to be moved up
    T tmp = data[idx]; 
    // move the element up to the appropriate position by comparing with its parent
    for (i = idx; data[i / 2]> tmp; i /= 2)
    data[i] = data[i / 2];
    data[i] = tmp;
}

template<typename T>
void NormalHeap<T>::perlocateDown(int idx) {
    int i, child;
    // save the element that needs to be moved down
    T tmp = data[idx]; 
    // move the element down to the appropriate position by comparing with its children
    for (i = idx; i * 2 <= data.size()-1; i = child)
    {
        // find the index of the smaller child
        child = i * 2;
        if (child != data.size() && data[child + 1] < data[child])
            child++;
        // move the element down if its child is smaller than it
        if (data[child] < tmp)
            data[i] = data[child];
        else
            break;
    }
    // put the saved element in the appropriate position
    data[i] = tmp; 
}

template<typename T>
T NormalHeap<T>::getMin() {
    // return the minimum element in the heap
    return data[1]; 
}

template<typename T>
void NormalHeap<T>::deleteMin() {
    // replace the root element with the last element
    data[1]=data[data.size()-1]; 
    // remove the last element in the vector
    data.pop_back(); 
    // move the root element down to the appropriate position
    perlocateDown(1); 
}

template<typename T>
NormalHeap<T>::NormalHeap() {
    // initialize the vector with a dummy element
    data.push_back(T()); 
}

#endif //P2_NORMALHEAP_H
