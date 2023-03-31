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
    // Definition of the SkewHeap node
    struct Node{
        T element;      
        Node* left;     
        Node* right;    
        // Constructor for the SkewHeap node
        Node(const T& _element,Node* _l= nullptr,Node* _r= nullptr):
                element(_element),left(_l),right(_r){}
    };
    // Function for merging two SkewHeaps
    Node* Merge(Node* h1,Node* h2);
    // Function for deleting all nodes in a SkewHeap
    void del(Node* a);
    Node* root; 
public:
    // Constructor for the SkewHeap
    SkewHeap():root(NULL){};
    // Function to check if the SkewHeap is empty
    bool isEmpty(){return root== nullptr;}
    // Function to insert an element into the SkewHeap
    void insert(const T&x);
    // Function to delete the minimum element from the SkewHeap
    void deleteMin();
    // Function to get the minimum element from the SkewHeap
    T getMin();
    // Destructor for the SkewHeap
    ~SkewHeap(){
        del(root);
    };
};

// Definition of the Merge function
template<typename T>
typename SkewHeap<T>::Node* SkewHeap<T>::Merge(SkewHeap::Node *h1, SkewHeap::Node *h2) {
    // Base case: If one of the SkewHeaps is empty, return the other SkewHeap
    if(h1== nullptr) return h2;
    if(h2== nullptr) return h1;

    // If the root of h1 is greater than the root of h2, swap them
    if(h1->element>h2->element)
        std::swap(h1,h2);

    // Merge the right child of h1 with h2
    if(h1->left== nullptr)
        h1->left=h2;
    else
    {
        h1->right= Merge(h1->right,h2);
        std::swap(h1->left,h1->right);
    }
    // Return the root of the merged SkewHeap
    return h1; 
}

// Definition of the insert function
template<typename T>
void SkewHeap<T>::insert(const T &x) {
    // Merge the SkewHeap with a new node containing x
    root= Merge(root,new Node(x)); 
}

// Definition of the del function
template<typename T>
void SkewHeap<T>::del(SkewHeap::Node *a) {
    // Base case: If the SkewHeap is empty, return
    if(a== nullptr) return; 
    // Delete the right child
    if(a->right!= nullptr) del(a->right); 
    // Delete the left child
    if(a->left!= nullptr) del(a->left);  
    // Delete the root of the SkewHeap 
    delete a; 
}

// Definition of the deleteMin function
template<typename T>
void SkewHeap<T>::deleteMin() {
    Node* old=root; 
    // Merge the left child and the right child
    root= Merge(old->left,old->right); 
    //delete root
    delete old;
}

template<typename T>
T SkewHeap<T>::getMin() {
    return root->element;
}


#endif //P2_SKEWHEAP_H
