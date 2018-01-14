//
// Created by MagieSmiley on 2018/1/14.
//

#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

#define OK 1
#define ERROR 0
#define OVERFLOW -1
#define MAX_SIZE 100

typedef int Status;
typedef int ElemType;

typedef struct term{
    int col,row;
    ElemType val;//非零元素
}Term;//即Tripple Sparse Matrix

typedef struct sparsematrix{
    int m,n,t;//t：实际非零元素个数
    Term table[MAX_SIZE+1];
}SparseMatrix;

Status CreatSparseMatix(SparseMatrix* M){
    if(!M) return ERROR;
    int i,m,n;
    ElemType val;
    Status k;
    cout<<"请输入矩阵的行数m,列数n,非零元素数t：";
    cin>> M->m >> M->n >> M->t;
    M->table[0].row=0;//行优先,table[0]不存放任何值，作为后面相加时的QHead（虚结点）
    for(i=1; i <= M->t; i++){
        do{
            cout<<"请按行优先输入第"<<i<<"个非零元素①所在的行m(1～"<<M->m <<
                ",② 列n(1～"<<M->n<<") 以及③对应的元素值val：",
                    cin>>m>>n>>val;
            k=0;
            if(m<1 || n<1 || m>M->m || n>M->n){
                cout<<"Out Of Bounds!Please input again!"<<endl;
                k=1;//行或列超出范围
            }
            /* 行或列的顺序有错. 如：m<当前所对应的第i个Term中的行数row */
            if(m<M->table[i-1].row || (m == M->table[i-1].row && n<= M->table[i-1].col)){
                cout<<"行或列的顺序有错！请按行优先顺序重新输入！"<<endl;
                k=1;
            }
        }while (k);
        M->table[i].row = m;
        M->table[i].col = n;
        M->table[i].val = val;
    }
    return OK;
}

void DestroySparseMatix(SparseMatrix* M){
    M->m = 0;
    M->n = 0;
    M->t = 0;
    free(M->table);
}

void OutPut(SparseMatrix M){
    if(!M.t) return;
    int col,row,val;
    for(int i=1; i<=M.m; i++){
        for(int j=1;j<=M.n;j++){
            row = M.table[i].row;
            col = M.table[i].col;
            val = M.table[i].val;
            if(i == row && j == col){
                cout<<val<<"\t";
            }else{
                cout<<0<<"\t";
            }
        }
        cout<<endl;
    }
    cout<<endl;
}

/* 由稀疏矩阵M复制得到T */
Status CopySparseMatix(SparseMatrix M,SparseMatrix *T){
    if(!T || !M.t || M.t<=0) return ERROR;
    *T=M;

    return OK;
}

int compare(int c1, int c2){
    int ret = c1-c2;
    if(ret<0){
        return -1;
    }else if(ret > 0){
        return 1;
    }else{
        return 0;
    }
}

/* 求稀疏矩阵的和Q=M+N */
Status AddSparseMatrix(SparseMatrix M, SparseMatrix N,SparseMatrix* Q){
    Term *Mstart,*Mend,*Nstart,*Nend,*Qhead,*Qval;
    if(M.m != N.m || M.n != N.n )
        return ERROR;
    Q->m = M.m;
    Q->n = M.n;
    Mstart = &M.table[1]; /* MStart的初值指向矩阵M的非零元素首地址（忽略0下标） */
    Nstart = &N.table[1];/* NStart初值指向矩阵N的非零元素首地址 */
    Mend = &M.table[M.t];//******* /* MEnd指向矩阵M的非零元素尾地址 */
    Nend = &N.table[N.t];
    Qhead = Qval = Q->table; /* Qh、Qe的初值指向矩阵Q的非零元素首地址的前一地址(即下标0处) */

    while (Mstart<=Mend && Nstart <= Nend) {
        Qval++;//Qval指针后移，以add M、N中的元素
        switch (compare(Mstart->row, Nstart->row)) {

            /* M、N矩阵当前非零元素的行相等,继续比较列 */
            case 0:
                switch (compare(Mstart->col, Nstart->col)) {
                    case 0://行列均相同，直接相加
                        *Qval = *Mstart;//因为无需深拷贝，故可以直接将Mstart->col/row/val信息全部赋给Qval
                        Qval->val += Nstart->val;//即 M+N对应元素相加
                        if(Qval->val == 0)
                            Qval--;/* 元素值为0，不存入压缩矩阵 */
                        Mstart++;
                        Nstart++;
                        break;

                    case 1://Mstart->col > Nstart->col,因为是行优先。先直接存储Nstart->col部分，然后Nstart++; 以便后续再进行下一轮比较.
                        //由于不是M+N对应元素相加，而是直接从Nstart复制而来，故不可能Qval->val出现0，无需判断这个。
                        *Qval = *Nstart;
                        Nstart++;
                        break;

                    case -1://Mstart->col < Nstart->col,因为是行优先。先直接存储Mstart->col部分，然后Mstart++; 以便后续再进行下一轮比较.
                        *Qval = *Mstart;
                        Mstart++;
                        break;

                }
                break;

            case 1://Mstart->row > Nstart->row, 行优先存储Nstart，然后Nstart++
                *Qval = *Nstart;
                Nstart++;
                break;

            case -1://Mstart->row < Nstart->row, 行优先存储Mstart，然后Mstart++
                *Qval = *Mstart;
                Mstart++;
                break;
        }
    }

    if(Mstart > Mend){//M先遍历到头（M中非零元素行下标比较小）。 /* 矩阵M的元素全部处理完毕 */
        //后续操作仅需将Nstart一个个attach到Qval后面即可
        while (Nstart <= Nend) {
            Qval++;//复制/attach之前，一定要保证Qval已后移
            *Qval = *Nstart;//attach N to Q
            Nstart++;
        }
    }
    if(Nstart > Nend){//N先遍历到头，原理同上
        while(Mstart <= Mend){//attach M to Q
            Qval++;
            *Qval = *Mstart;
            Mstart++;
        }
    }

    Q->t = Qval - Qhead;
    return OK;
}


void PrintSMatrix(SparseMatrix M)
{ /* 输出稀疏矩阵M */
    int i;
    printf("%d行%d列%d个非零元素。\n",M.m,M.n,M.t);
    printf("行  列  元素值\n");
    for(i=1;i<=M.t;i++)
        printf("%2d%4d%8d\n",M.table[i].row,M.table[i].col,M.table[i].val);
}


Status FastTransposeSparseMatrix(SparseMatrix M, SparseMatrix* T){
    if(!T || !M.t || M.t <= 0) return ERROR;
    int col,*num,*cntNonSeroSum;
    num = (ElemType*)malloc((M.n+1)*sizeof(ElemType));//因为0下标处不存储值，有效列下标：1~M.n，故开辟空间时，需要+1（开辟0~M.n个空间，其中首位置弃用）
    cntNonSeroSum = (ElemType*)malloc((M.n+1)*sizeof(ElemType));
    T->m = M.n; T->n = M.m; T->t = M.t;//基本转置操作。
    for(int j=1; j<=M.n; j++)
        num[j] = 0;/* 设初值 */
    for(int j=1; j<=M.t; j++)
        num[M.table[j].col]++; /* 求M中每一列(对应N中某一行)含非零元素个数 */

    for(int j=1; j<=M.n; j++){
        cntNonSeroSum[j] = 0;
    }
    for(int j=2; j<=M.n; j++){
        cntNonSeroSum[j] = cntNonSeroSum[j-1]+num[j-1];//动规
    }
    for(int i=1; i<=M.t; i++){
        int index = cntNonSeroSum[M.table[i].col]++;//获取M中第i个非零元素（共t个）的列下标处（对应T中某行下标）的非零元素总数
        //一定要注意index+1!!! 因为下标从1开始，首位（下标0）弃用! index也应该保持一致！！！
        T->table[index+1].row = M.table[i].col;
        T->table[index+1].col = M.table[i].row;
        T->table[index+1].val = M.table[i].val;//关键在于找到i与index的映射关系
    }

    free(num);
    free(cntNonSeroSum);
    return OK;
}

int main(){
    SparseMatrix M,N,R,T,Q;
    CreatSparseMatix(&M);
    cout<<"\nCreatSparseMatix(&M): "<<endl;
    OutPut(M);

    //    cout<<"\nTransposeSparseMatrix(M, &T): "<<endl;
    //    TransposeSparseMatrix(M, &T);
    //    OutPut(T);
    //

    FastTransposeSparseMatrix(M, &N);
    cout<<"\nFastTransposeSparseMatrix(M, &N): "<<endl;
    OutPut(N);

    //    cout<<"\nOutPut(R): "<<endl;
    //    CreatSparseMatix(&R);
    //    OutPut(R);

    //    CopySparseMatix(M, &N);
    //    OutPut(N);


    AddSparseMatrix(M, N, &Q);
    cout<<"\nAddSparseMatrix(M, N, &Q): "<<endl;
    OutPut(Q);
}
