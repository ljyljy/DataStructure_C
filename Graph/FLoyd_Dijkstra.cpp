
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
//#include <memory.h>

#define INFINITY 10000
using namespace std;

//不好。O(n^3)
void Floyd1(const vector<vector<int>>& graph, vector<vector<int>>& shortestPath)
{
    shortestPath = graph;
    int size = (int)graph.size();
    for(int k = 0; k < size; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(shortestPath[i][j] > shortestPath[i][k] + shortestPath[k][j]){
                    shortestPath[i][j] = shortestPath[i][k] + shortestPath[k][j];
                }
            }
        }
    }
}

//若要求最短路径, 仅需记录前驱(见Dijkstra中的MinPath()) / 后继(如本方法)
void MinPath(int start, int end, const vector<vector<int>>& next, vector<int>& path)
{
    path.push_back(start);
    int temp_start = start;
    while (temp_start != end){
        temp_start = next[temp_start][end];//啥?_?
        path.push_back(temp_start);
    }
}

//求最短路径值的同时，顺手记录后继结点 (记录下最短路径具体结点)。
void Floyd2(const vector<vector<int>>& graph, vector<vector<int>>& shortestPath,
            vector<vector<int>>& next)
{
    shortestPath = graph;
    int size = (int)graph.size();

    //先找到每个节点的直接后继
    //如next[0][4] = 4; 即4 (next[0][4])是 0的后继结点之一(❤️此处指的是下标!!实际上是指"5是1的后继结点之一"!)
    for(int i = 0; i <size; i++){
        for(int j = 0; j < size; j++){
            next[i][j] = j;  //直接后继。
        }
    }
    //Floyd算法 求最短路径
    for(int k = 0; k < size; k++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(shortestPath[i][j] > shortestPath[i][k] + shortestPath[k][j]){
                    shortestPath[i][j] = shortestPath[i][k] + shortestPath[k][j];
                    next[i][j] = next[i][k];//顺便将后继结点更新。让j的后继便为k
                    //注意for循环的顺序！ 外中内循环分别为k, i, j!!
                }
            }
        }
    }
}

//////////////////////////

void Print(const vector<vector<int> >& graph)
{
    int size = (int)graph.size();
    int i,j;
    cout << '\t';
    for(i = 0; i < size; i++)
        cout << i << '\t';
    cout << '\n';

    for(i = 0; i < size; i++)
    {
        cout << i << ":\t";
        for(j = 0; j < size; j++)
        {
            if(graph[i][j] == INFINITY)
                cout << "-\t";
            else
                cout << graph[i][j] << '\t';
        }
        cout << '\n';
    }
    cout << "======\n\n\n";
}

void Print(int start, int end, int length, const vector<int>& a)
{
    if(length == INFINITY)
        return;
    //cout << '(' << start+1 << " , " << end+1 << "):\t";
    cout << end << ":\t";
    if(length == INFINITY)
    {
        cout << "∞\n";
        return;
    }
    cout << length << '\t';

    int size = (int)a.size();
    for(int i = 0; i < size; i++)
    {
        cout << a[i]+1;
        if(i != size-1)
            cout << " → ";
    }
    cout << '\n';
}

void Print2(const vector<int>& a)
{
    int size = (int)a.size();
    for(int i = 0; i < size; i++)
    {
        cout << a[i] << '\t';
    }
    cout << '\n';
}

void MinPath3(int start, int end, const vector<vector<int> >& next, vector<int>& path)
{
    path.push_back(start);
    int s = start;
    while(s != end)
    {
        s = next[s][end];
        path.push_back(s);
    }
}

void MinPath2(int start, int end,
              const vector<int>& pre, vector<int>& path)
{
    path.push_back(end);
    int e = end;
    while(start != e)
    {
        e = pre[e];
        path.push_back(e);
    }
    reverse(path.begin(), path.end());
}

void Min_Floyd(const vector<vector<int> >& graph)
{
    int N = (int)graph.size();
    vector<vector<int> > sp(N, vector<int>(N, INT_MAX));    //最短路径的值
    vector<vector<int> > next(N, vector<int>(N, -1));        //直接后继
    Floyd2(graph, sp, next);

    //输出所有结点间的最短路径
    vector<int> path;
    int i,j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            path.clear();
            MinPath(i, j, next, path);
            Print(i, j, sp[i][j], path);
        }
    }
}

//graph：邻接矩阵，src：源点，sp[i]：src到i的最短路径的长度
void Dijkstra(const vector<vector<int> >& graph, int src, vector<int>& sp)
{
    int N = (int)graph.size();
    vector<bool> s(N, false);    //集合S初始化为空
    sp = graph[src];            //从src到任意点的直接路径

    //将src加入集合S
    s[src] = true;
    sp[src] = 0;
    int num,k,j;
    int mp;
    for(num = 1; num < N; num++)    //将剩余的N-1个结点加入到集合S
    {
        k = -1;        //候选结点编号
        mp = -1;    //最短路径值
        for(j = 0; j < N; j++)
        {
            if(s[j])
                continue;
            if((mp < 0) || (mp > sp[j]))
            {
                mp = sp[j];
                k = j;
            }
        }
        s[k] = true;
        for(j = 0; j < N; j++)
        {
            if(s[j])
                continue;
            sp[j] = min(sp[j], sp[k]+graph[k][j]);
        }
    }
}

//graph：邻接矩阵，src：源点，sp[i]：src到i的最短路径的长度
void Dijkstra2(const vector<vector<int> >& graph, int src, vector<int>& sp, vector<int>& pre)
{
    int N = (int)graph.size();
    vector<bool> s(N, false);    //集合S初始化为空
    sp = graph[src];            //从src到任意点的直接路径

    //将src加入集合S
    s[src] = true;
    sp[src] = 0;
    int num,k,j;
    int mp;
    for(num = 1; num < N; num++)    //将剩余的N-1个结点加入到集合S
    {
        k = -1;        //候选结点编号
        mp = -1;    //最短路径值
        for(j = 0; j < N; j++)
        {
            if(s[j])
                continue;
            if((mp < 0) || (mp > sp[j]))
            {
                mp = sp[j];
                k = j;
            }
        }
        s[k] = true;
        for(j = 0; j < N; j++)
        {
            if(s[j])
                continue;
            if(sp[j] > sp[k]+graph[k][j])
            {
                sp[j] = sp[k]+graph[k][j];
                pre[j] = k;
            }
        }
    }
}

int main03()
{
    const int N = 8;
    vector<vector<int>> graph(N, vector<int>(N, INFINITY));
    graph[0][5] = 24;
    graph[0][4] = 70;//对应边1->6
    graph[0][2] = 47;//对应边1->3
    graph[1][3] = 31; graph[1][6] = 74; graph[1][7] = 79;
    graph[2][1] = 55; graph[2][3] = 88; graph[2][4] = 23; graph[2][6] = 46;
    graph[3][7] = 29;
    graph[4][1] = 31; graph[4][6] = 42;
    graph[5][2] = 25; graph[5][3] = 120;
    graph[6][7] = 66;

    vector<vector<int>> shortestPath(N, vector<int>(N, INT_MAX));//最短路径的值
    vector<vector<int>> next(N, vector<int>(N, -1));//直接后继
    Floyd2(graph, shortestPath, next);

    //Min_Floyd(graph);

    int src = 0;
    vector<int> sp(N);
    vector<int> pre(N, src);
    Dijkstra2(graph, 0, sp, pre);
    Print2(sp);
    Print2(pre);
    //输出src到其他所有结点间的最短路径
    vector<int> path;
    for(int j = 0; j < N; j++)
    {
        path.clear();
        MinPath2(src, j, pre, path);
        Print(src, j, sp[j], path);
    }

    return 0;
}

/*
 * 结果：

    0	101	47	132	70	24	93	159
    0	4	0	1	0	0	2	6
    0:	0	1
    1:	101	1 → 5 → 2
    2:	47	1 → 3
    3:	132	1 → 5 → 2 → 4
    4:	70	1 → 5
    5:	24	1 → 6
    6:	93	1 → 3 → 7
    7:	159	1 → 3 → 7 → 8
    Program ended with exit code: 0

 */