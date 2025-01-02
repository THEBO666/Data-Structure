#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
void Print(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout<<std::endl;
}
int PartSort(int *a, int left, int right)
{
    // 以左边为基准，要先走右找小，再走左找大
    int key = left;
    while (left < right)
    {

        while (left < right && a[right] >= a[key])
        {
            right--;
        }
        while (left < right && a[left] <= a[key])
        {
            left++;
        }
        std::swap(a[left], a[right]);
    }
    std::swap(a[left], a[key]);
    Print(a,6);
    return left;
}

/*int PartSort(int *a,int left,int right)
{
     // 以左边为基准，要先走左找大，再走右找小
    int key=right;
    while(left<right)
    {
        while(left<right&&a[left]<=a[key])
        {
            left++;
        }
        while(left<right&&a[right]>=a[key])
        {
            right--;
        }
        std::swap(a[left],a[right]);
    }
    std::swap(a[left],a[key]);
    return left;
}*/
// 排序范围[left,right)
void QuickSort(int *a, int left, int right)
{
    if (left >= right)
        return;
    int key = PartSort(a, left, right);
    QuickSort(a, left, key - 1);
    QuickSort(a, key + 1, right);
}

void SelectSort(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int minIndex = i;
        for (int j = i; j < n; j++)
        {
            if (a[minIndex] > a[j])
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
            std::swap(a[minIndex], a[i]);
    }
}
void _Merge(int *a, int left, int right, int *tmp)
{
    if (left >= right)
        return;
    int mid = (left) + (right - left) / 2;
    _Merge(a, left, mid, tmp);
    _Merge(a, mid + 1, right, tmp);
    int begin1 = left, end1 = mid;
    int begin2 = mid + 1, end2 = right;
    int i = left;
    while (begin1 <= end1 && begin2 <= end2)
    {
        if (a[begin1] < a[begin2])
            tmp[i++] = a[begin1++];
        else
            tmp[i++] = a[begin2++];
    }
    // 当遍历完其中一个区间，将另一个区间剩余的数据直接放到tmp的后面
    while (begin1 <= end1)
        tmp[i++] = a[begin1++];
    while (begin2 <= end2)
        tmp[i++] = a[begin2++];
    // int j=0;
    for (int j = left; j <= right; j++)
        a[j] = tmp[j];
}
void MergeSort(int *a, int n)
{
    int *tmp = (int *)malloc(sizeof(int) * n);
    _Merge(a, 0, n - 1, tmp);
    free(tmp);
}
int main()
{
    int a[] = {46,79,56,38,40,84};
    int n = sizeof(a) / sizeof(a[0]);
    QuickSort(a, 0,n-1);
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    return 0;
}
