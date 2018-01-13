//
// Created by MagieSmiley on 2017/12/19.
//



#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <memory.h>

using namespace std;

//查找图的联通分量
class UnionFindSet {
private:
    int m_nN;
    int* m_pParent;
public:
    UnionFindSet(int n);
    ~UnionFindSet();
    void Union(int i, int j);
    int Find(int i);
    void Print() const;
    int CalcComponent(int N);
};

//m_pParent[i] = j ---- 第i个结点的父节点是j
UnionFindSet::UnionFindSet(int n) {
    m_nN = n;
    m_pParent = new int[m_nN];
    for(int i = 0; i < m_nN; i++){
        m_pParent[i] = i;//默认自己是自己的父节点m_pParent
    }
}

UnionFindSet::~UnionFindSet() {
    if(m_pParent){
        delete[] m_pParent;
        m_pParent = NULL;
    }
}

int UnionFindSet::Find(int i) {
    if(i<0 || i>= m_nN)
        return -1;

    int root = i;
    while (root != m_pParent[root]){//若当前根节点root（i）不是root的父节点
        root = m_pParent[root];//则root = root的父节点(注意本循环内不要改变传入的i值！！！)
    }
    //循环结束后，root为i结点的根节点

    //为了简化计算量，将Find()复杂度降为O(n)--> 压缩路径如下。
    int tmp = i;
    while (tmp != root){//第一次Find() 彻底遍历一遍：将遍历过的所有点的父节点直接指向根节点。这样 后序的查找会加速很多。
        m_pParent[tmp] = root;//将当前遍历结点的父节点直接更改为根节点
        tmp = m_pParent[tmp];//为了将父节点的父节点们一个个改为根节点，故用while循环。
    }
    return root;
}

void UnionFindSet::Union(int i, int j) {
    if( i<0 || j<0|| i>= m_nN|| j>= m_nN)
        return;

    int root_i = Find(i);
    int root_j = Find(j);
    if(root_i != root_j){//若二者的父节点不一样，则将其一设为另一个结点的父节点(本次无特殊要求，则随意)
        m_pParent[root_i] = root_j;
    }
}

int UnionFindSet::CalcComponent(int N)
{
    //    const int N = 10;
    //    UnionFindSet ufs(N);
    //    ufs.Union(2,6);
    //    ufs.Union(5,6);
    //    ufs.Union(1,8);
    //    ufs.Union(2,9);
    //    ufs.Union(5,3);
    //    ufs.Union(4,8);
    //    ufs.Union(4,0);
    int *component = new int[N];//每个连通分量的结点数
    memset(component, 0, N* sizeof(int));
    for(int i = 0; i < N; i++){
        int root_i = this->Find(i);//this: 调用者，即UnionFindSet的实例
        component[root_i]++;
    }
    int nComponent;//连通分量的总数
    for(int i = 0; i < N; i++){
        if(component[i] != 0){
            nComponent++;
        }
    }
    delete[] component;
    return nComponent;
}

int main02()
{
    const int N = 10;
    UnionFindSet ufs(N);
    ufs.Union(2,6);
    ufs.Union(5,6);
    ufs.Union(1,8);
    ufs.Union(2,9);
    ufs.Union(5,3);
    ufs.Union(4,8);
    ufs.Union(4,0);
    int nComponent = ufs.CalcComponent(N);
    cout << "ufs的联通分量为:" << nComponent << endl;
}