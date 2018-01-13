#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "DivideConquer/DivideConquer.h"
#include "DivideConquer/ListNode.h"

using namespace std;



int main()
{
    char a[] =  "abca";  //此时的size也可以为sizeof(a) / sizeof(char) - 1 ；  法②/*{ 'a','b','c','d'};*/
    int size = (int)strlen(a); //法②：/* sizeof(a) / sizeof(char);*/
    cout << size << endl;
    Permutations(a, size, 0);
    return 0;
}
