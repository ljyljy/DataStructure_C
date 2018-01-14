//
// Created by MagieSmiley on 2017/11/8.
//

#ifndef DATASTRUCTURE_BINTREE_H
#define DATASTRUCTURE_BINTREE_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <mm_malloc.h>

using namespace std;

//#define ERROR 0
//#define OK 1
//#define OVERFLOW 2
//#define NotPresent 4
//#define Duplicate 5
//
//typedef int Status;

typedef struct element_type
{
    int Key;
    char Data;
}ElemType;

typedef struct bst_node
{
    ElemType Element;
    bst_node *left, *right;
}BSTNode;

typedef struct bs_tree{
    bst_node *root;
}BSTree;

void Creat(BSTree* Bst)
{
    Bst->root = NULL;
}

void preorder(BSTNode* root, int layer)
{
    if(!root)
        return;
    for(int i = 0; i< layer; i++){
        cout << "--";
    }
    cout << root->Element.Key << endl;
    preorder(root->left, layer+1);
    preorder(root->right, layer+1);
}

void inorder(BSTNode* root, int layer)
{
    if(!root)
        return;
    for(int i = 0; i< layer; i++){
        cout << "--";
    }
    preorder(root->left, layer+1);
    cout << root->Element.Key << endl;
    preorder(root->right, layer+1);
}

BSTNode* Search_Recursion(BSTNode* root, ElemType Element){
    if(!root)
        return NULL;

    if(root->Element.Key == Element.Key){
        return root;
    } else if(root->Element.Key > Element.Key){
        return Search_Recursion(root->left, Element);
    } else{
        return Search_Recursion(root->right, Element);
    }
}

BSTNode* CreatNode(ElemType element)
{
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if(!node)
        return NULL;
    node->Element.Key = element.Key;
    node->left = node->right = NULL;
    return node;
}
//注意事项：
//root
BSTNode* Insert(BSTNode* &root, ElemType ele)
{
    if(!root){
        root = CreatNode(ele);
        root = Insert(root, ele);
    }
    else if (root->Element.Key > ele.Key){
        root->left = Insert(root->left, ele);
    }else if (root->Element.Key < ele.Key){
        root->right = Insert(root->right, ele);
    }else if (root->Element.Key == ele.Key){
        cout << "Duplicate!" << endl;
        return NULL;
    }
    return root;
}

/**
 * 在根指针root所指二叉树中递归查找关键字为key的元素。
 *  若查找成功，则指针p指向该元素节点，返回true;
 *  若查找失败，则指针p指向查找路径上的最后一节点，返回false。指针pParent指向root的双亲，其初始调用值为NULL.
 *
 * @param pParent 指针pParent指向root的双亲，其在main()中的初始调用值为NULL.
 * @param p 指向(成功)目标节点 或(失败)查找路径上的最后节点
 * @return 查找结果
 */
bool SearchV2(BSTNode* root, int key ,BSTNode* pParent, BSTNode* &p)
{
    if(!root){
        p = pParent;
        return false;
    }

    if(root->Element.Key == key){//查找成功
        p = root;
        return true;
    } else if(root->Element.Key > key){
        return SearchV2(root->left, key, root, p);//注意！pParent传入的是当前的root
    } else{ // if(root->Element.Key < key){
        return SearchV2(root->right, key, root, p);
    }
}

/**
 * 待删结点只有单支。
 * @param root 有左or右子树的待删结点。需要将其左右孩子重新连接。
 * @param prev 待删结点的前继结点
 * @return
 */
bool DelNodeWithChild(BSTNode* &root, BSTNode* &prev)
{
    if(!root)
        return false;
    if(prev->left == root){
        prev->left = root->left? root->left : root->right;//因为待删结点root只有一个单支！
    }else if(prev->right == root){
        prev->right = root->right? root->right : root->left;//因为待删结点root只有一个单支！
    }
    free(root);
    root = NULL;

    return true;
}


/**
 * 需找到root的最左孩子（右子树"头"的最小节点），替代被删节点的位置。
 * WHY? 因为右子树"头"的最小节点刚好满足 大于root左子树所有节点 小于root右子树所有节点（除自己外）
 *
 * 【注意】传引用！ 必须是root的右子树树头的最左孩子。若root有许多嵌套右子树。
 * 由BST的Insert()算法：那些子右子树的最左孩子 一定是大于其父亲的最左孩子的！
 *
 * @param root 有左右孩子的待删结点。需要将其左右孩子重新连接。
 * @param min  待删结点的替代者 && 右子树中的最小的结点。
 *             先将替代结点min赋值为 root的右子树"头"。最终目的是找到待删结点root的最左孩子。
 *
 *
 * [更正]但是右子树"头"可以存在嵌套子树。这时的最左孩子是最深嵌套子树的最左孩子！！
 */
bool DelNodeWithChildren(BSTNode* &root)
{
    if(!root)
        return false;
    BSTNode* min = root->right; //先将替代结点min赋值为 root的右子树"头"。最终目的是找到待删结点root的最左孩子(即右子树中的最小的结点)！！！
    BSTNode* prevMin = root;//prev为(待删结点的)替代结点min的前继结点
    while (min->left){
        prevMin = min;
        min = min->left;
    }
    root->Element.Key = min->Element.Key;
    //还需考虑到替代者min的是否存在右子树！若存在，则需要将替代者min的右子树结点连接到前继结点的子树上。
    if(prevMin->right == min)//TODO: TEST (这是啥情况?。? 可能存在？？？）
        prevMin->right = min->right;
    else //prev->right != min (prev存在其他右子树)
        prevMin->left = min->right;//注意：既然是最左子树，则min不可能有左孩子

    free(min);
    min = NULL;
    return true;
}

/**
 * 删除二叉树中 值为key的结点。并将删除后的断裂二叉树重新连接。
 * @param key 待删结点的key值
 * @param ele 可不用。（用于返回已删除元素ele）
 * @return
 */
bool Delete(BSTNode* root, int key, ElemType &ele)
{
    if(!root)
        return false;
    BSTNode *prev, *node2Del = root;
    while (node2Del && key != node2Del->Element.Key){//注意：与key比较的是node2Del的key 而非root的key
        prev = node2Del;//node2Del的前继结点
        if(key > node2Del->Element.Key){
            node2Del = node2Del->right;
        } else {    //if(key < node2Del->Element.Key)
            node2Del = node2Del->left;
        }
    }
    if(!node2Del)
        return false;//若上面的while循环一直未找到key结点，则会遍历完后退出循环，此时node2Del为NULL。说明未找到。

    ele.Key = key;//用于返回已删除元素ele。该参数一般不是必须的。
    if(node2Del->left && node2Del->right){
        DelNodeWithChildren(node2Del);
    }else {//if(  (!node2Del->left && !node2Del->right)  ||  node2Del->left   ||   node2Del->right){
        DelNodeWithChild(node2Del, prev);
//    }else{//leaf
//        free(node2Del);
//        node2Del = NULL;
//    }
        return true;
    }


int main01(int argc, const char * argv[]) {
    BSTree* bst = (BSTree*)malloc(sizeof(BSTree));
    Creat(bst);
    BSTNode* root = bst->root;

    for(int i = 0; i<10; i+=2){
        ElemType ele;
        ele.Key = i;
        Insert(root, ele);
    }
    inorder(root, 0);

    return 0;
}






//////////////

template <typename T>
struct TreeNode{
    int val;
    TreeNode* next;
    TreeNode* m_root;
};

template <typename T>
class BSTree {
protected:
    TreeNode<T>* m_root;
public:
    BSTree(){
        m_root = NULL;
    }
    virtual bool insert(TreeNode<T>* node) = 0;
    virtual bool insert(TreeNode<T>* parent, const T& value) = 0;

};
/////////////

#endif //DATASTRUCTURE_BINTREE_H
