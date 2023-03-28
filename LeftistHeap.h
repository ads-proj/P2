//
// Created by andres on 2023-03-28.
//

#ifndef P2_LEFTISTHEAP_H
#define P2_LEFTISTHEAP_H
#include "algorithm"
using namespace std;
template <typename T>
class LeftistHeap {
private:
    struct Node{
        T element;
        Node* left;
        Node* right;
        int npl;
        Node(const T& _element,Node* _l= nullptr,Node* _r= nullptr,int _npl=0):
            element(_element),left(_l),right(_r),npl(_npl){}
    };
    Node* Merge(Node* h1,Node* h2);
    T getMin();
    void del(Node* a);
    Node* root;
public:
    LeftistHeap():root(NULL){};

    void insert(const T&x);
    void deleteMin();
    ~LeftistHeap(){
        del(root);
    };
};

template<typename T>
typename LeftistHeap<T>::Node* LeftistHeap<T>::Merge(LeftistHeap::Node *h1, LeftistHeap::Node *h2) {
    if(h1== nullptr) return h2;
    if(h2== nullptr) return h1;
    if(h1->element>h2->element)
        std::swap(h1,h2);
    if(h1->left== nullptr)
        h1->left=h2;
    else
    {
        h1->right= Merge(h1->right,h2);
        if(h1->left->npl<h1->right->npl)
            std::swap(h1->left,h1->right);
        h1->npl=h1->right->npl+1;
    }
    return h1;
}

template<typename T>
void LeftistHeap<T>::insert(const T &x) {
    root= Merge(root,new Node(x));
}

template<typename T>
void LeftistHeap<T>::del(LeftistHeap::Node *a) {
    if(a->right!= nullptr) del(a->right);
    if(a->left!= nullptr) del(a->left);
    delete a;
}

template<typename T>
void LeftistHeap<T>::deleteMin() {
    Node* old=root;
    root= Merge(old->left,old->right);
    delete old;
}

template<typename T>
T LeftistHeap<T>::getMin() {
    return root->element;
}


#endif //P2_LEFTISTHEAP_H
