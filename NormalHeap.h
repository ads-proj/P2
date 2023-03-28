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
    void perlocateUp(int idx);
    void perlocateDown(int idx);

public:
    NormalHeap();
    void insert(const T& t);
    T getMin();
    void deleteMin();
    bool isEmpty(){return data.size()==1;}
};

template<typename T>
void NormalHeap<T>::insert(const T &t) {
    data.push_back(t);
    perlocateDown(data.size()-1);
}

template<typename T>
void NormalHeap<T>::perlocateUp(int idx) {
    int i;
    T tmp = data[idx];
    //judge whether the father node's length is smaller than its
    //length and adjust it to the nearest ancestor whose length smalller than it.
    for (i = idx; data[i / 2]> tmp; i /= 2)
        data[i] = data[i / 2];
    data[i] = tmp;
}

template<typename T>
void NormalHeap<T>::perlocateDown(int idx) {
    int i, child;
    T tmp = data[idx];
    //judge whether the children node's length is smaller than it.
    //length and adjust it to the nearest children whose length all bigger than it.
    for (i = idx; i * 2 <= data.size()-1; i = child)
    {
        //find the child index
        child = i * 2;
        //find the smaller child index
        if (child != data.size() && data[child + 1] < data[child])
            child++;
        //judge whether the child is smaller than it
        if (data[child] < tmp)
            //adjust the heap
            data[i] = data[child];
        else
            //if adjust finish return
            break;
    }
    data[i] = tmp;
}

template<typename T>
T NormalHeap<T>::getMin() {
    return data[1];
}

template<typename T>
void NormalHeap<T>::deleteMin() {
    data[1]=data[data.size()-1];
    data.pop_back();
    perlocateDown(1);
}

template<typename T>
NormalHeap<T>::NormalHeap() {
    data.push_back(T());
}


#endif //P2_NORMALHEAP_H
