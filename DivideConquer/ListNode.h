//
// Created by MagieSmiley on 2017/11/7.
//

#ifndef DATASTRUCTURE_LISTNODE_H
#define DATASTRUCTURE_LISTNODE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;

class ListNode {
public:
    int val;
    ListNode* next;
    ListNode(int v):val(v), next(NULL){}
};


#endif //DATASTRUCTURE_LISTNODE_H
