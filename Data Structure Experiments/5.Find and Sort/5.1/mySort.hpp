#pragma once

#include <iostream>
// 所有排序为升序
template <class T>
void InsertSort(T *a, int n)
{
    for (int i = 1; i < n; i++)
    {
        int end = i - 1;
        T temp = a[i];
        while (end >= 0)
        {
            if (temp < a[end])
            {
                a[end + 1] = a[end];
                end--;
            }
            else
            {
                break;
            }
        }
        a[end + 1] = temp;
    }
}

template <class T>
void ShellSort(T *a, int n, int gap)
{
    // int gap = 100001;
    if (gap % 2 == 0)
        gap += 1;
    while (gap > 1)
    {
        gap = gap / 3 + 1;
        for (int i = 0; i < n - gap; i++)
        {
            int end = i;
            T temp = a[end + gap];
            while (end >= 0)
            {
                if (temp < a[end])
                {
                    a[end + gap] = a[end];
                    end -= gap;
                }
                else
                {
                    break;
                }
            }
            a[end + gap] = temp;
        }
    }
}

template <class T>
void SelectSort(T *a, int n)
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
            if (minIndex != i)
                std::swap(a[minIndex], a[i]);
        }
    }
}

template <class T>
void AdjustDown(T *a, int parent, int n)
{
    int child = 2 * parent + 1;
    while (child < n)
    {
        if (child + 1 < n && a[child + 1] < a[child])
            child++;
        if (a[child] < a[parent]) // 小则交换，构建小根堆
        {
            std::swap(a[child], a[parent]);
            parent = child;
            child = 2 * parent + 1;
        }
        else
        { // 没有交换则不需要交换
            break;
        }
    }
}

template <class T>
void HeapSort(T *a, int n)
{
    for (int i = n - 1 - 1 / 2; i >= 0; i--)
        AdjustDown(a, i, n);
    for (int i = n - 1; i > 0; i--)
    {
        std::swap(a[0], a[i]);
        AdjustDown(a, 0, i);
    }
}

template <class T>
void BubbleSort(T *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        bool flag = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                std::swap(a[j], a[j + 1]);
                flag = true;
            }
        }
        if (!flag)
            break;
    }
}

template <class T>
int minIndex(T *a, int left, int right) // 快速排序三数取中优化法
{
    int mid = (left + right) / 2;
    if (a[left] < a[right])
    {
        if (a[mid] < a[left])
        {
            return left;
        }
        else if (a[mid] > a[right])
        {
            return right;
        }
        else
        {
            return mid;
        }
    }
    else
    {
        if (a[mid] > a[left])
        {
            return left;
        }
        else if (a[mid] < a[right])
        {
            return right;
        }
        else
        {
            return mid;
        }
    }
}

template <class T>
int PartSort(T *a, int left, int right)
{
    int mid = minIndex(a, left, right);
    std::swap(a[mid], a[right]);
    int key = right; // 一定要注意快速排序是左还是右作为基准值，右边的话传参(0,N-1)
    while (left < right)
    {
        while (left < right && a[left] <= a[key])
        {
            left++;
        }
        while (left < right && a[right] >= a[key])
        {
            right--;
        }
        std::swap(a[left], a[right]);
    }
    std::swap(a[left], a[key]);
    return left;
}

template <class T>
void QuickSort(T *a, int left, int right)
{
    if (left >= right)
        return;
    int key = PartSort(a, left, right);
    QuickSort(a, left, key - 1);
    QuickSort(a, key + 1, right);
}
