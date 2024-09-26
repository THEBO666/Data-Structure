#include <iostream>
#include <cassert>
#define InitSize 5

// 对于顺序存储的队列，将其写为循环队列会增强其可用性
// 而对于链式存储来说实现更为简单

template <class T>
class SeqQueue{
    
public:
    SeqQueue():a(nullptr),capacity(InitSize),_size(0)
    {
        a=(T*)malloc(sizeof(T)*InitSize);
    }
    void push(T x)
    {
        if(capacity==_size)
        {
            T *temp=(T*)realloc(a,sizeof(T)*capacity*2);
            if(temp==nullptr)
            {
                perror("malloc fail");
                return ;
            }
            a=temp;
            capacity*=2;
        }
        a[_size++]=x;
    }
    void pop()
    {
        assert(_size!=0);
        for(int i=0;i<_size-1;i++)
        {
            a[i]=a[i+1];
        }
        _size--;
    }
    bool empty()
    {
        return _size==0;
    }
    T front()
    {
        return a[0];
    }
    T back()
    {
        return a[_size-1];
    }
    int size()
    {
        return _size;
    }
private:
    T *a;
    int _size;
    int capacity;
};