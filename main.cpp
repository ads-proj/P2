//
// Created by andres on 2023-03-28.
//
#include "iostream"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "normalHeap.h"
#include "Node.h"
typedef struct road
{
    int vfrom, vnext;
    int length;
}road;
int main()
{
    int n,m;

    NormalHeap<node> t;
    for(int i=1;i<=15;i++)
    {
        node k;
        k.v=1;k.length=i*10;
        t.insert(k);
    }
    t.deleteMin();
    printf("hello");
}