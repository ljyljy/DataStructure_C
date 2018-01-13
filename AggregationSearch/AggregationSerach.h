//
// Created by MagieSmiley on 2017/11/8.
//

#ifndef DATASTRUCTURE_AGGREGATIONSERACH_H
#define DATASTRUCTURE_AGGREGATIONSERACH_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
typedef int ElemType ;

using namespace std;

typedef struct 
{
    int n;
    int maxLength;
    ElemType* elemType;
}listSet;

int Search(listSet L, ElemType x){
    int i;
    for(i = 0; L.elemType[i] < x; i++);
        if(L.elemType[i] == x) {
            return i;
        };
    return -1;
}
#endif //DATASTRUCTURE_AGGREGATIONSERACH_H
