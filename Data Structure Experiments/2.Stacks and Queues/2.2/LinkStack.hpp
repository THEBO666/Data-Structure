#include <iostream>
#include <cassert>

template <class T>

struct SNode{
    T data;
    SNode *next;
    SNode(T a):data(a),next(nullptr){}
};

template <class T>

class LinkStack{
    typedef SNode<T> SNode;
public:
    LinkStack():_size(0),head(nullptr){}
    void push(T x)
    {
        SNode *node=new SNode(x);
        if(head==nullptr)
        {
            head=node;
        }
        else
        {
            node->next=head;
            head=node;
        }
        _size++;
        
    }
    void pop()
    {
        assert(_size!=0);
        if(head->next==nullptr)
        {
            delete head;
            head=nullptr;
        }
        else
        {
            SNode *temp=head->next;
            delete head;
            head=temp;
        }
        _size--;
    }
    int size()
    {
        return _size;
    }
    T top()
    {
        assert(_size!=0);
        return head->data;
    }
    bool empty()
    {
        return _size==0;
    }

    ~LinkStack(){}
private:
    int _size;
    SNode *head;
    
};