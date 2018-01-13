
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

typedef int TElemType;
//typedef bool(*VISIT) (BinaryTreeNode* root);

typedef struct BinaryTreeNode {
    TElemType Data;
    BinaryTreeNode *lChild, *rChild;
}BinaryTreeNode, *BinTree;

void Visit(BinaryTreeNode* root) {
    if (!root) {
        return;
    }
    cout << root->Data << " ";
}

/**
 *    先序遍历创建二叉树
 */
void PreCreatBinTree(BinTree &BT)
{
    TElemType data;
    data = getchar();
    if (data == '#') {
        BT = NULL;
    }
    else
    {
        BT = (BinTree)malloc(sizeof(BinaryTreeNode));//生成根节点
        if (!BT) {
            exit(0);
        }
        BT->Data = data;
        PreCreatBinTree(BT->lChild);
        PreCreatBinTree(BT->rChild);
    }
}
void InitTree(BinTree &BT) {
    BT = NULL;
}

void DestroyBinTree(BinTree &BT) {
    //释放所有的树结点，并把指向树根的指针置空
    //只能用后序free，否则需要1个（中序）或2个（前序）临时变量
    //来保存BT->LChild和BT->RChild
    if (BT != NULL) {
        DestroyBinTree(BT->lChild);
        DestroyBinTree(BT->rChild);
        delete BT;
    }
}

/*---------(递归/非递归) 遍历二叉树-----------*/
void PreOrderTraverse(BinTree BT) {
    if (BT != NULL) {
        Visit(BT); //访问根结点
        PreOrderTraverse(BT->lChild);//先序访问左子树
        PreOrderTraverse(BT->rChild);//先序访问右子树
    }
}
void PreOrderTraverse2(BinTree BT) {
    if (!BT) {
        return;
    }
    stack<BinaryTreeNode*> s;
    s.push(BT);
    BinaryTreeNode* pCur;
    while (!s.empty())
    {
        pCur = s.top();
        s.pop();
        Visit(pCur);
        if (pCur->rChild) {//因为是stack, 进栈顺序应为先右后左！
            s.push(pCur->rChild);
        }
        if (pCur->lChild) {
            s.push(pCur->lChild);
        }
    }
}

void InOrderTraverse(BinTree BT) {
    if (BT != NULL) {
        PreOrderTraverse(BT->lChild);//中序访问左子树
        Visit(BT); //访问根结点
        PreOrderTraverse(BT->rChild);//中序访问右子树
    }
}

void PostOrderTraverse(BinTree BT) {
    if (BT != NULL) {
        PreOrderTraverse(BT->lChild);//后序访问左子树
        PreOrderTraverse(BT->rChild);//后序访问右子树
        Visit(BT); //访问根结点
    }
}

/**
 * 查找二叉树中结点值为data的结点
 *
 * 说明：
 *   查找操作可选用先序、中序和后序查找中的任一种都可，这里采用的是先序的查找。
 */
BinTree FindNode(BinTree BT, const TElemType &data)
{
    //返回二叉树BT中值为val的结点的指针
    //若c不存在于BT中，则返回NULL
    if (!BT)
        return NULL;
    else if (BT->Data == data) //找到相应的结点，返回其指针
        return BT;

    BinTree BT2 = NULL;
    BT2 = FindNode(BT->lChild, data);   //在其左子树中进行查找
    if (!BT2)      //没有找到，则继续在其右子树中进行查找
        BT2 = FindNode(BT->rChild, data);

    return BT2;
}

int BiTreeDepth(BinTree BT)
{
    //求树的最大深度
    //从二叉树深度的定义可知，二叉树的深度应为其左、右子树深度的最大值加1，
    //因为根结点也算1层。
    if (BT == NULL) {  //若为空树，则返回0
        return 0;
    }
    else
    {
        int leftDepth = BiTreeDepth(BT->lChild); //求左树的深度
        int rightDepth = BiTreeDepth(BT->rChild); //求右树的深度
        return leftDepth >= rightDepth ? leftDepth + 1 : rightDepth + 1;
    }
}

/**
 *   获得值为data的结点的双亲结点（先序遍历）
 *
 *   说明：在判断其左孩子或右孩子的值前，首先要判断其左孩子或右孩子是否为空，例如，若BT的左子树为空，则表达式BT->LChild->cData这样的语句是会产生异常的，所以在判等之前一定要检查其孩子是否为空。
 *          此外，函数返回NULL意味着有两种可能的情况，一是此结点为树的根结点（根结点没有双亲结点），二是这个结点不存在于树中。
 *          所以在应用时，如果检测到返回值为NULL则还要判断值为c的结点是否是根结点，若它不是根结点，则表示在树BT中不存在值为c结点。
 */
BinTree GetParent(BinTree BT, const TElemType &data)
{
    //若BT不存在于或值为data的结点为根，则返回NULL
    if (!BT || BT->Data == data)
        return NULL;

    if ((BT->lChild && BT->lChild->Data == data) ||
        (BT->rChild && BT->rChild->Data == data)) {
        return BT;
    }

    BinTree Parent = NULL;
    Parent = GetParent(BT->lChild, data);
    if (Parent == NULL)
        Parent = GetParent(BT->rChild, data);
    return Parent;
}

/**
 *    返回二叉树BT中结点的最大值  (先序遍历)(分治递归)
 *
 *    说明：
 *        默认以树根作为当前最大结点tmp;
 *        (分治)先找出左子树的最大结点,再找出右子树的最大结点
 */
BinTree GetMax(BinTree BT)
{
    if (!BT)
        return NULL;

    BinaryTreeNode *pMax = BT;
    BinaryTreeNode *tmp = GetMax(BT->lChild);
    if (tmp != NULL)
    {
        if (tmp->Data > pMax->Data)
            pMax = tmp;
    }

    tmp = GetMax(BT->rChild);
    if (tmp != NULL)
    {
        if (tmp->Data > pMax->Data)
            pMax = tmp;
    }
    return pMax;
}

/**
 *    返回二叉树BT中叶子结点的个数 (分治)
 *
 *        分治：分别计算出左、右叶子结点个数，然后再累加到leafNum上。
 */
int GetLeafNum(BinTree BT)
{
    if (!BT)
        return 0;

    int leafNum = 0;
    if (!BT->rChild && !BT->lChild) {
        leafNum++;
    }
    else
    {
        leafNum += GetLeafNum(BT->lChild);
        leafNum += GetLeafNum(BT->rChild);
    }
    return leafNum;
}

/**
 *    返回二叉树BT中非叶子结点的个数 (分治)
 *
 *    说明：
 *        若为BT为空树或为叶子结点，返回0
 *
 *        (分治)分别计算出左、右非叶子结点个数，然后再累加到nonLeafNum上。
 *
 *    注意：根结点也是一个非叶子结点 !
 */
int GetNonLeafNum(BinTree BT)
{
    //返回二叉树BT中非叶子结点的个数
    if (BT == NULL || (!BT->lChild && !BT->rChild))
        return 0;
    else
    {
        int nonLeafNum = 1; //每次调用时的当前根结点也是一个非叶子结点
        //分治
        nonLeafNum += GetNonLeafNum(BT->lChild);
        nonLeafNum += GetNonLeafNum(BT->rChild);
        return nonLeafNum;
    }
}
