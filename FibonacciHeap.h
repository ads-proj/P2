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
    struct Node{
        T key;
        int degree;
        Node* left;
        Node* right;
        Node* parent;
        Node* child;
        Node()=default;
        Node(const T&_key)
        {
            key=_key;
            degree=0;
            left=right=parent=child= nullptr;
        }
        void insertLeft(Node* tmp)
        {
            left->right=tmp;
            tmp->right=this;
            tmp->left=left;
            left=tmp;
        }
        void remove()
        {
            left->right=right;
            right->left=left;
        }
        void attach(Node *y);

    };
    int keyNum;
    Node * min;
    void consolidate();
public:
    FibonacciHeap();
    void insert(const T& key);
    T getMin();
    void deleteMin();
    bool isEmpty();
};

template<typename T>
void FibonacciHeap<T>::Node::attach(FibonacciHeap::Node *y) {
    y->remove();
    if(child== nullptr) child=y;
    else
       child->insertLeft(y);
    y->parent=this;
    degree++;
}

template<typename T>
FibonacciHeap<T>::FibonacciHeap() {
    keyNum=0;
    min= nullptr;
}

template<typename T>
void FibonacciHeap<T>::insert(const T& key) {
    Node* tmp=new Node(key);
    tmp->left=tmp->right=tmp;
    if(min== nullptr) min=tmp;
    else
    {
        min->insertLeft(tmp);
        if(min->key>tmp->key) min=tmp;
    }
    keyNum++;
}

template<typename T>
void FibonacciHeap<T>::deleteMin() {
    while(min->child!= nullptr)
    {
        Node *child=min->child;
        if(child->right==child)
            min->child= nullptr;
        else
            min->child=child->right;
        child->remove();
        min->insertLeft(child);
        child->parent= nullptr;
    }
    min->remove();
    if(min->right==min) min=NULL;
    else
    {
        min=min->right;
        consolidate();
    }
    keyNum--;
}

template<typename T>
void FibonacciHeap<T>::consolidate() {
    vector<Node*> h;
    h.resize((int)log2(keyNum)+3);
    for(int i=0;i<h.size();i++) h[i]= nullptr;
    while(min!= nullptr)
    {
        Node* x=min;
        min->remove();
        if(min->right==min) min= nullptr;
        else min=min->right;
        x->left=x->right=x;
        int d=x->degree;
        while(h[d]!= nullptr)
        {
            auto y=h[d];
            if(x->key>y->key)
                std::swap(x,y);
            x->attach(y);
            h[d]=NULL;
            d++;
        }
        h[d]=x;
    }
    min= nullptr;
    for(int i=0;i<h.size();i++)
    {
        if(h[i]!= nullptr)
        {
            if(min== nullptr)
                min=h[i],min->left=min->right=min;
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
    return min->key;
}

template<typename T>
bool FibonacciHeap<T>::isEmpty() {
    return min== nullptr;
}

#endif //P2_FIBONACCIHEAP_H
