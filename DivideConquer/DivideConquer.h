//
// Created by MagieSmiley on 2017/11/7
//

#ifndef DATASTRUCTURE_DIVIDECONQUER_H
#define DATASTRUCTURE_DIVIDECONQUER_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>
#include "ListNode.h"


using namespace std;

/**
 * @param n 盘子总数
 * @param a src
 * @param b middle
 * @param c dest
 */
//                      src    mid     dest
void HanoiTower(int n, char a, char b, char c){
    if(n == 1){
        cout << a << "->" << c << endl;
    } else{
        HanoiTower(n-1, a, c, b);//将a上放n-1个盘子从a移到b(借助c)
        HanoiTower(1, a, b, c);//将a上最下方的1个盘子从a移到c(借助b)
        HanoiTower(n-1, b, a, c);//再将b上的n-1个盘子从b移到c(借助a)
    }
}


int getStrlen(const char* s){
    if(!s || *s == '\0'){
        return 0;
    }
    return 1 + getStrlen(s+1);

    //写法2(一行代码实现)
    return s? (*s? 1 + getStrlen(s+1) : 0 ):0;
}

void permutation(const char* s, char* e){
    if(*s == '\0'){
        cout << e << endl;
    } else{
        int len = (int)strlen(s);
//        strlen()功能：计算字符串s的(unsigned int型）长度 ———— 返回s的长度，不包括结束符NULL。
//        返回的是size_t型，也就是unsigned int型，表示的范围是比int更大的。
        for(int i = 0; i < len; i++){
            if(i != 0 || s[0] != s[i]){
                swap(s[0], s[i]);
                permutation(s+1, e);
                swap(s[0], s[i]);
            }
        }
    }
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == NULL){
        return l2;//l2 may be NULL
    }else if(l2 == NULL){// l1 != NULL
        return l1;
    }

    if(l1->val < l2->val){
        // ListNode l1_ = l1->next;
        // ListNode ret = mergeTwoLists(l1_,l2);

        // l1->next = ret;
        // return l1;

        //压缩 简写：
        return (l1->next = mergeTwoLists(l1->next, l2), l1);
        //逗号表达式!!!实则返回的是l1~~~
    }else{
        // ListNode l2_ = l2->next;
        // ListNode ret = mergeTwoLists(l1,l2_);

        // l2->next = ret;
        // return l2;
        return (l2->next = mergeTwoLists(l1, l2->next), l2);
    }
}

/**
 * 【逆序】打印值为偶数的链表节点的值
 * @param node
 */
void printEvenListNode(ListNode* node){
    if(!node){
        return;
    }
    printEvenListNode(node->next);
    if((node->val%2) == 0){
        cout << node->val << endl;
    }
}

template <int SIZE>
class QueueSolution {
protected:
    enum {
        N = SIZE + 2//包括 左&右 / 上&下 的两个边界
    };
    struct Pos{
        int x, y;
        Pos(int px = 0, int py = 0):x(px), y(py){}
    };
    int m_chessboard[N][N];
    Pos m_direction[3];//因为只需判断当前皇后的三个方向：左下(-1,-1), 正下方(0,-1), 右下(1,-1)
    list<Pos> m_solution;
    int m_count;

    void init(){
        m_count = 0;
        //初始化边界
        for(int i = 0; i < N; i+=(N-1)){
            for(int j = 0; j < N; j++){
                m_chessboard[i][j] = 2;//初始化行边界
                m_chessboard[j][i] = 2;//初始化列边界
            }
        }
        //初始化棋盘上非边界部分
        for(int i = 1; i <= SIZE; i++){
            for(int j = 0; j < N; j++){
                m_chessboard[i][j] = 0;
            }
        }
        m_direction[0].x = -1; m_direction[0].y = -1;//左下
        m_direction[1].x = 0;  m_direction[1].y = -1;//正下方
        m_direction[2].x = 1;  m_direction[2].y = -1;//右下方
    }

    void printChessboard(){
//        for(m_solution.move(0), !m_solution.end(), !m_solution.empty()){
//            cout << "(" << m_solution.current().x << ", " << m_solution.current().y << ")" << endl;
//        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                switch (m_chessboard[i][j]){
                    case 0:
                        cout << " " << endl;
                        break;
                    case 1://皇后位置
                        cout << "#" << endl;
                        break;
                    case 2://边界
                        cout << "*" << endl;
                        break;

                }
            }
        }
    }

    bool check(int x, int y, int d){
        bool flag = true;
        do{
            x += m_direction[d].x;
            y += m_direction[d].y;
            flag = flag && (m_chessboard[x][y] == 0);
        }
    }
};

#endif //DATASTRUCTURE_DIVIDECONQUER_H

