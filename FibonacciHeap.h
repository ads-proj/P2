//
// Created by andres on 2023-03-28.
//

#ifndef P2_FIBONACCIHEAP_H
#define P2_FIBONACCIHEAP_H
#include "algorithm"
#include "vector"
#include "cmath"
using namespace std;
template <typename T>

class FibonacciHeap {
private:
    // define a node structure
    struct Node {
        T key;
        int degree;
        Node* left;
        Node* right;
        Node* parent;
        Node* child;
        Node() = default;
        Node(const T& _key) {
            key = _key;
            degree = 0;
            left = right = parent = child = nullptr;
        }
        // method to insert a node to the left of this node
        void insertLeft(Node* tmp) {
            left->right = tmp;
            tmp->right = this;
            tmp->left = left;
            left = tmp;
        }
        // method to remove this node from the doubly linked list
        void remove() {
            left->right = right;
            right->left = left;
        }
        // method to attach a node as the child of this node
        void attach(Node* y);
    };
    int keyNum;
    Node* min;
    // method to consolidate the heap after deleting the minimum node
    void consolidate();
public:
    // constructor
    FibonacciHeap();
    // method to insert a key into the heap
    void insert(const T& key);
    // method to get the minimum key in the heap
    T getMin();
    // method to delete the minimum key in the heap
    void deleteMin();
    // method to check if the heap is empty
    bool isEmpty();
};

// method to attach a node as the child of this node
template <typename T>
void FibonacciHeap<T>::Node::attach(Node* y) {
    y->remove();
    if (child == nullptr)
        child = y;
    else
        child->insertLeft(y);
    y->parent = this;
    degree++;
}

// constructor
template <typename T>
FibonacciHeap<T>::FibonacciHeap() {
    keyNum = 0;
    min = nullptr;
}

// method to insert a key into the heap
template <typename T>
void FibonacciHeap<T>::insert(const T& key) {
    Node* tmp = new Node(key);
    tmp->left = tmp->right = tmp;
    if (min == nullptr) min = tmp;
    else 
    {
        min->insertLeft(tmp);
        if (min->key > tmp->key) min = tmp;
    }
    keyNum++;
}

// method to delete the minimum key in the heap
template <typename T>
void FibonacciHeap<T>::deleteMin() {
    // remove the children of the minimum node and insert them into the root list
    while (min->child != nullptr) 
    {
        Node* child = min->child;
        if (child->right == child)
            min->child = nullptr;
        else
            min->child = child->right;
        child->remove();
        min->insertLeft(child);
        child->parent = nullptr;
    }
    // remove the minimum node from the root list
    min->remove();
    if (min->right == min)
        min = nullptr;
    else 
    {
        min = min->right;
        consolidate();
    }
    keyNum--;
}

// method to consolidate the heap after deleting the minimum node
template<typename T>
void FibonacciHeap<T>::consolidate() {
    vector<Node*> h;
    // Resize the vector to hold (log2(keyNum) + 3) nodes.
    h.resize((int)log2(keyNum)+3);
    // Initialize
    for(int i=0;i<h.size();i++) h[i]= nullptr;

    while(min!= nullptr)
    {
        // Remove the current minimum node from the root list.
        Node* x=min;
        min->remove();
        if(min->right==min) min= nullptr;
        else min=min->right;

        // Set the left and right pointers of the minimum node to itself.
        x->left=x->right=x;
        int d=x->degree;
        // Merge nodes with the same degree until there are no more nodes with the same degree.
        while(h[d]!= nullptr)
        {
            auto y=h[d];
            if(x->key>y->key)
                std::swap(x,y);
            // Attach the other node as a child of the minimum node.
            x->attach(y);
            h[d]=NULL;
            // Increase the degree of the minimum node.
            d++;
        }
        // Store the minimum node
        h[d]=x;
    }

    min= nullptr;
    // Loop through the vector and insert all non-null nodes into the root list.
    for(int i=0;i<h.size();i++)
    {
        if(h[i]!= nullptr)
        {
            // If the root list is empty, set the minimum node to the current node.
            if(min== nullptr)
                min=h[i],min->left=min->right=min;
            // Otherwise, insert the current node to the left of the minimum node,
            // and update the minimum node if necessary.
            else
            {
                min->insertLeft(h[i]);
                if(min->key>h[i]->key) min=h[i];
            }
        }
    }
}

template<typename T>
T FibonacciHeap<T>::getMin() {
    // Return the key of the minimum node.
    return min->key;
}

template<typename T>
bool FibonacciHeap<T>::isEmpty() {
    // Return true if the heap is empty, false otherwise.
    return min== nullptr;
}

#endif //P2_FIBONACCIHEAP_H
