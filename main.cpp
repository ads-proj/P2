//
// Created by andres on 2023-03-28.
//
#include "iostream"
#include "limits"
#include "LeftistHeap.h"
#include "SkewHeap.h"
#include "normalHeap.h"
#include "Node.h"
struct Edge{
    int v,w,next;
    Edge()=default;
    Edge(int _v,int _w,int _next):v(_v),w(_w),next(_next){};
};
vector<Edge> edge;
vector<int> head;
vector<int> tra;
int main()
{
    int n,m,startP=0;
    cin>>n>>m>>startP;
    startP-=1;
    head.resize(n);
    tra.resize(n);
    for(int i=0;i<n;i++) head[i]=-1;
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        u-=1,v-=1;
        edge.emplace_back(v,w,head[u]);
        head[u]=edge.size()-1;

    }

    for(int i=0;i<head.size();i++)
        tra[i]= std::numeric_limits<int>::max();
    tra[startP]= 0;
    SkewHeap<node> heap;
    heap.insert({startP,0});
    while(!heap.isEmpty())
    {
        node tmp=heap.getMin();
        heap.deleteMin();
        int t=head[tmp.v];
        if(tmp.length>tra[tmp.v]) continue;
        while(t!=-1)
        {
            if(tmp.length+edge[t].w<tra[edge[t].v])
            {
                heap.insert({edge[t].v,tmp.length+edge[t].w});
                tra[edge[t].v]=tmp.length+edge[t].w;
            }
            t=edge[t].next;
        }
    }
    for(int i=0;i<head.size();i++)
        cout<<tra[i]<<endl;
    return 0;
}