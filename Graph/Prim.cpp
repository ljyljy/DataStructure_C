//
// Created by MagieSmiley on 2017/12/20.
//


#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <list>
//#include <memory.h>

#define INFINITY 10000
using namespace std;

struct Edge{
    int x,y;
    int val;
    Edge(){
        x = y = 0;
        val = INFINITY;
    }

    Edge(int a, int b, int v){
        x = a;
        y = b;
        val = v;
    }
};

void AddEdge(list<Edge>& edgeList, int from,
             const vector<vector<int>>& graph, const vector<bool>& tickVec)
{
    int N = (int)graph.size();
    for(int j = 0; j < N; j++) {
        if(graph[from][j] != INFINITY && !tickVec[j]) {
            //边(from, j)存在，且结点j尚未加入集合tickVec
            edgeList.push_back(Edge(from, j, graph[from][j]));
        }
    }
}

Edge MinEdge(list<Edge> edgelist)
{
    if(edgelist.empty()){
        return NULL;
    }
    int minVal = INT_MAX;
    Edge minEdge = edgelist.front();
    for(Edge e : edgelist){
        if(minVal > e.val){
            minVal = e.val;
            minEdge = e;
        }
    }
    return minEdge;
}

bool Prim(const vector<vector<int>>& graph, vector<Edge>& MST){
    int N = (int)graph.size();
    vector<bool> tickVec(N, false);//初始化路径
    list<Edge> edgelist;//s与~s的所有边
    tickVec[0] = true;//任选结点(如0)加入tickVec中
    AddEdge(edgelist, 0, graph, tickVec);//添加以起点为0的所有边

    Edge minEdge;
    for(int i = 1; i < N; i++) {
        if(edgelist.empty())
            return false;
        minEdge = MinEdge(edgelist);
        MST[i-1] = minEdge;//添加到MST(最小生成树)中
        for(int j = 0; j < N; j++){
            tickVec[minEdge, j] = true;

            cout<<"\ntickVec[minEdge, j]: "<<tickVec[minEdge, j]<<endl;
            cout<<"tickVec[j]: "<<tickVec[ j]<<endl;
//未完待续....

        }



    }
}