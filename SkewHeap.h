//
// Created by andres on 2023-03-28.
//

#ifndef P2_SKEWHEAP_H
#define P2_SKEWHEAP_H
#include "algorithm"
using namespace std;
template <typename T>
class SkewHeap {
private:
    struct Node{
        T element;
        Node* left;
        Node* right;
        Node(const T& _element,Node* _l= nullptr,Node* _r= nullptr):
                element(_element),left(_l),right(_r){}
    };
    Node* Merge(Node* h1,Node* h2);
    void del(Node* a);

    Node* root;
public:
    SkewHeap():root(NULL){};
    bool isEmpty(){return root== nullptr;}
    void insert(const T&x);
    void deleteMin();
    T getMin();
    ~SkewHeap(){
        del(root);
    };
};

template<typename T>
typename SkewHeap<T>::Node* SkewHeap<T>::Merge(SkewHeap::Node *h1, SkewHeap::Node *h2) {
    if(h1== nullptr) return h2;
    if(h2== nullptr) return h1;
    if(h1->element>h2->element)
        std::swap(h1,h2);
    if(h1->left== nullptr)
        h1->left=h2;
    else
    {
        h1->right= Merge(h1->right,h2);
        std::swap(h1->left,h1->right);
    }
    return h1;
}

template<typename T>
void SkewHeap<T>::insert(const T &x) {
    root= Merge(root,new Node(x));
}

template<typename T>
void SkewHeap<T>::del(SkewHeap::Node *a) {
    if(a== nullptr) return;
    if(a->right!= nullptr) del(a->right);
    if(a->left!= nullptr) del(a->left);
    delete a;
}

template<typename T>
void SkewHeap<T>::deleteMin() {
    Node* old=root;
    root= Merge(old->left,old->right);
    delete old;
}

template<typename T>
T SkewHeap<T>::getMin() {
    return root->element;
}


#endif //P2_SKEWHEAP_H
