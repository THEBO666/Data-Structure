#include <iostream>
#include "mySort.hpp"
#include <vector>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <cstdlib>

void Print(int *a, int n)
{
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
}
int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}
void TestSort()
{
    srand(time(0));
    const int N = 10000;
    int *a1 = (int *)malloc(sizeof(int) * N);
    int *a2 = (int *)malloc(sizeof(int) * N);
    int *a3 = (int *)malloc(sizeof(int) * N);
    int *a4 = (int *)malloc(sizeof(int) * N);
    int *a5 = (int *)malloc(sizeof(int) * N);
    int *a6 = (int *)malloc(sizeof(int) * N);
    int *a7 = (int *)malloc(sizeof(int) * N);
    int *a8 = (int *)malloc(sizeof(int) * N);
    for (int i = 0; i < N; ++i)
    {
        a1[i] = rand();
        a2[i] = a3[i] = a4[i] = a5[i] = a6[i] = a7[i] = a8[i] = a1[i];
    }
    int begin1 = clock();
    InsertSort(a1, N);
    int end1 = clock();
    int begin2 = clock();
    ShellSort(a2, N, N * 0.1 + 1);
    int end2 = clock();
    int begin3 = clock();
    SelectSort(a3, N);
    int end3 = clock();
    int begin4 = clock();
    HeapSort(a4, N);
    int end4 = clock();
    int begin5 = clock();
    BubbleSort(a5, N);
    int end5 = clock();
    int begin6 = clock();
    QuickSort(a6, 0, N - 1);
    int end6 = clock();
    int begin7 = clock();
    qsort(a7, N, sizeof(int), cmp);
    int end7 = clock();
    int begin8 = clock();
    std::sort(a8, a8 + N);
    int end8 = clock();
    // Print(a2+10000,100);
    // std::cout<<std::endl;
    // Print(a8+10000,100);
    printf("InsertSort:%d\n", end1 - begin1);
    printf("ShellSort:%d\n", end2 - begin2);
    printf("SelectSort:%d\n", end3 - begin3);
    printf("HeapSort:%d\n", end4 - begin4);
    printf("BubbleSort:%d\n", end5 - begin5);
    printf("QuickSort:%d\n", end6 - begin6);
    printf("C qsort:%d\n", end7 - begin7);
    printf("C++ STL sort:%d\n", end8 - begin8);
    free(a1);
    free(a2);
    free(a3);
    free(a4);
    free(a5);
    free(a6);
    free(a7);
    free(a8);
}

int main()
{
    TestSort();
    return 0;
}
