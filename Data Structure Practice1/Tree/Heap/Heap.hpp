#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

template <class T>
struct Heap
{
    T *a;
    int size;
    int capacity;
    Heap() {};
    Heap(int _capacity)
    {
         capacity=_capacity;
         size=0;
        a = (T *)malloc(sizeof(T) * capacity);
    }
    Heap(T *arr, int n)
    {
        a = (T *)malloc(n * sizeof(T));
        if (a == NULL)
        {
            perror("malloc fail");
            return;
        }
        size = capacity = n;
        memcpy(a, arr, n * sizeof(T));
        for (int i = (n - 1 - 1) / 2; i >= 0; i--)
            AdjustDown(a, n, i);
    }
    void HeapInit()
    {
        assert(a);
        a = (T *)malloc(sizeof(T) * 4);
        if (a == NULL)
        {
            perror("malloc fail");
            return;
        }
        size = 0;
        capacity = 4;
    }

    void AdjustUp(T *arr, int child)
    {
        int parent = (child - 1) / 2;
        while (child > 0)
        {
            if (arr[child] > arr[parent])
            {
                std::swap(arr[child], arr[parent]);
                child = parent;
                parent = (child - 1) / 2;
            }
            else
            {
                break;
            }
        }
    }

    void AdjustDown(T *arr, int n, int parent)
    {
        int child = parent * 2 + 1;
        while (child < n)
        {
            if (child + 1 < n && arr[child + 1] < arr[child])
            {
                ++child;
            }
            if (arr[child] < arr[parent])
            {
                std::swap(arr[child], arr[parent]);
                parent = child;
                child = 2 * parent + 1;
            }
            else
            {
                break;
            }
        }
    }
    void HeapPush(T x)
    {
        assert(a);
        if (size == capacity)
        {
            T *temp = (T *)realloc(a, sizeof(T) * capacity * 2);
            if (a == NULL)
            {
                perror("malloc fail");
                return;
            }
            a = temp;
            capacity *= 2;
        }
        a[size] = x;
        size += 1;
        AdjustUp(a, size - 1);
    }
    void HeapPop()
    {
        assert(a);
        assert(!HeapEmpty());
        std::swap(a[0], a[size - 1]);
        --size;
        AdjustDown(a, size, 0);
    }
    T HeapTop() { return a[0]; }
    bool HeapEmpty() { return size == 0; }
    void HeapPrint()
    {
        for (int i = 0; i < size; i++)
            std::cout << a[i] << " ";
        std::cout << std::endl;
    }
    void HeapSort(T *arr, int n)
    {
        // for (int i = 1; i < n; i++) {
        /// hp.AdjustUp(arr, i);
        //}
        for (int i = (n - 1 - 1) / 2; i >= 0; i--)
        {
            AdjustDown(arr, n, i);
        }
        for (int i = n - 1; i > 0; i--)
        {
            std::swap(arr[0], arr[i]);
            AdjustDown(arr, i, 0);
        }
    }
    ~Heap()
    {
    }
};
