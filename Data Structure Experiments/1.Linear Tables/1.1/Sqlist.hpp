#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>

#define InitSize 5
template <class T>
class Sqlist
{
public:
    Sqlist():data(nullptr),_size(0),capacity(0)
    {
    }
    void InitSqlist()
    {
        data = (T *)malloc(sizeof(T) * InitSize);
        if (data == nullptr)
        {
            perror("malloc fail");
            return;
        }
        capacity = InitSize;
    }

    void push_back(T x)
    {
        check_capacity();
        data[_size++] = x;
    }
    void pop_back()
    {
        _size--;
    }
    size_t find(T x)
    {
        for (int i = 0; i < _size; i++)
        {
            if (data[i] == x)
                return i + 1; // 查找成功返回i+1
        }
        return 0; // 失败返回0
    }
    void insert(size_t pos,T x) // 这里设置为向后插入，即在pos之前
    {
        assert(pos <= _size);
        int end = _size - 1;
        pos+=1;
        while (end>=0&&end >=pos)
        {
            data[end + 1] = data[end];
            --end;
        }
        data[pos] = x;
        _size++;
    }
    void erase(int pos) // 删除该位置的值,从0开始
    {
        assert(pos <= _size);
        int begin = pos + 1;
        while (begin < _size)
        {
            data[begin - 1] = data[begin];
            begin++;
        }
        _size--;
    }
    T &operator[](size_t pos)
    {
        assert(pos <= _size);
        return data[pos];
    }
    size_t size()
    {
        return _size;
    }
    ~Sqlist()
    {
        delete data;
    }
private:
    void check_capacity()
    {
        if (capacity == _size)
        {
            T *temp = (T *)realloc(data, sizeof(T) * capacity * 2);
            if (temp == nullptr)
            {
                perror("malloc fail");
                return;
            }
            data = temp;
            capacity *= 2;
        }
    }

    T *data;
    size_t _size;
    size_t capacity;
};