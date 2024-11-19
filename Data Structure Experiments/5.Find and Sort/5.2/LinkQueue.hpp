#include <iostream>
#include <cassert>
#include <cstdlib>

template <class T>

struct QNode
{
    T data;
    QNode *next;
    QNode(T a) : data(a), next(nullptr) {}
};
// 使用链式存储实现队列，便于实现其操作
template <class T>

class LinkQueue
{
    typedef QNode<T> QNode;

public:
    LinkQueue() : head(nullptr), tail(nullptr), _size(0) {}
    void push(T x)
    {
        QNode *node = new QNode(x);
        if (head == nullptr)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            tail = node;
        }
        _size++;
    }
    void pop()
    {
        assert(_size != 0);

        if (head->next == nullptr)
        {
            free(head);
            head = nullptr;
        }
        else
        {
            QNode *temp = head->next;
            delete head;
            head = temp;
        }

        _size--;
    }

    bool empty()
    {
        return _size == 0;
    }
    size_t size()
    {
        return _size;
    }
    T front()
    {
        assert(_size != 0);
        return head->data;
    }
    T back()
    {
        assert(_size != 0);
        return tail->data;
    }
    ~LinkQueue()
    {
        QNode *cur = head;
        while (cur)
        {
            QNode *temp = cur->next;
            free(cur);
            cur = temp;
        }
        head = tail = nullptr;
        _size = 0;
    }

private:
    QNode *head;
    QNode *tail;
    int _size;
};