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
// Define a struct for the nodes in the heap
    struct Node{
        T element;
        Node* left;
        Node* right;

        //Null Path Length
        int npl;

        // Constructor for the node
        Node(const T& _element,Node* _l= nullptr,Node* _r= nullptr,int _npl=0):
            element(_element),left(_l),right(_r),npl(_npl){}
    };
    Node* Merge(Node* h1,Node* h2);
    T getMin();
    void del(Node* a);
    Node* root;
public:
    LeftistHeap():root(NULL){};
    bool isEmpty(){return root== nullptr;}
    void insert(const T&x);
    void deleteMin();
    ~LeftistHeap(){
    del(root);
    };
};

//method to merge two LeftistHeaps
template<typename T>
typename LeftistHeap<T>::Node* LeftistHeap<T>::Merge(LeftistHeap::Node *h1, LeftistHeap::Node *h2) {
    // Check if either heap is empty
    if(h1== nullptr) return h2;
    if(h2== nullptr) return h1;
    // Swap the heaps if necessary
    if(h1->element>h2->element)
        std::swap(h1,h2);
    // Merge the heaps
    if(h1->left== nullptr)
        h1->left=h2;
    else
    {
        h1->right= Merge(h1->right,h2);
        // Swap the left and right children if the left has a smaller null path length
        if(h1->left->npl<h1->right->npl)
        std::swap(h1->left,h1->right);
        // Set the null path length
        h1->npl=h1->right->npl+1;
    }
    return h1;
}

// insert a new node
template<typename T>
void LeftistHeap<T>::insert(const T &x) {
// Merge the new node with the root
    root= Merge(root,new Node(x));
}

// method to delete a node and its child
// used to release memory in the destructor.
template<typename T>
void LeftistHeap<T>::del(LeftistHeap::Node *a) {
    // Check if the node is null
    if(a== nullptr) return;
    // Recursively delete the right and left children
    if(a->right!= nullptr) del(a->right);
    if(a->left!= nullptr) del(a->left);
    // Delete the node
    delete a;
}

// method to delete the minimum element
template<typename T>
void LeftistHeap<T>::deleteMin() {
    // Save the old root node
    Node* old=root;
    // Merge the left and right children to create the new root
    root= Merge(old->left,old->right);
    // Delete the old root
    delete old;
}

// method to get the minimum element
template<typename T>
T LeftistHeap<T>::getMin() {
    // Return the root element
    return root->element;
}

#endif //P2_LEFTISTHEAP_H
