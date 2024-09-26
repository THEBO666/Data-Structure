#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>
#define InitSize 5
template <class T>

// version -1
class SeqStack{
public:
    SeqStack():a(nullptr),_size(0),capacity(InitSize)
    {
        a=(T*)malloc(sizeof(T)*InitSize);
    }
    void push(T  x)
    {
        if(_size==capacity)
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
        _size--;
    }
    T top()
    {
        assert(_size!=0);
        return a[_size-1];
    }

    bool empty()
    {
        return _size==0;
    }
    int size()
    {
        return _size;
    }
    ~SeqStack(){}
private:
    T *a;
    int _size;
    int capacity;
};
// version -2
// class Stack{
// public:
//     void push(T x)
//     {
//         _con.push_back(x);
//     }
//     void pop()
//     {
//         assert(_con.size()!=0);
//         _con.pop_back();
//     }
//     bool empty()
//     {
//         return _con.empty();
//     }
//     T top()
//     {
//         assert(_con.size()!=0);
//         return _con[_con.size()-1];
//     }
//     size_t size()
//     {
//         return _con.size();
//     }
// private:
//     std::vector<T> _con;
// };