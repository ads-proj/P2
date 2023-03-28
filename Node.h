//
// Created by andres on 2023-03-28.
//

#ifndef P2_NODE_H
#define P2_NODE_H
struct node{
    int v;
    int length;
    node(){v=0,length=0;}
    node(int _v,int _length):v(_v),length(_length){};
    friend bool operator<=(const node&a,const node&b) {
        return a.length <= b.length;
    }
    friend bool operator>(const node&a,const node&b){
        return !(a<=b);
    }
    friend bool operator<(const node&a,const node&b) {
        return a.length < b.length;
    }
    friend bool operator>=(const node&a,const node&b){
        return !(a<b);
    }
};
#endif //P2_NODE_H
