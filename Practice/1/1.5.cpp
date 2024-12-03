// 删除重复元素
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>

struct SqList
{
    int arr[50];
    int size;
};

void deleteSame(SqList &sq)
{
    int i,j;
    for (i = 0, j = 1; j < sq.size; j++)
    {
        if(sq.arr[i]!=sq.arr[j])
        {
            sq.arr[++i]=sq.arr[j];
        }
    }
    sq.size=i+1;
}
int main()
{
    int a[] = {1, 2, 2, 2, 3, 3, 3, 4, 5, 5};
    SqList sq;
    memcpy(sq.arr, a, 10 * sizeof(int));
    sq.size = 10;
    deleteSame(sq);
    for (int i = 0; i <sq.size; i++)
    {
        std::cout << sq.arr[i] << " ";
    }
    sq.size = 10;
}