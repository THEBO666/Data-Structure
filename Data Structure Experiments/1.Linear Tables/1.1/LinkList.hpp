#pragma once

#include <iostream>
#include <cassert>

template <class T>
struct ListNode // 结点
{
    T val;
    ListNode *next;
    ListNode() {}
    ListNode(const T a) : val(a), next(nullptr) {}
};

template <class T>
class LinkList
{
    typedef ListNode<T> Node;

public:
    LinkList() : _size(0)
    {
        head = new Node(0); // 设置哨兵位
        head->next = head;
        tail = head;
    }
    void insert(int pos, T x) // 从head之后开始，开始为0，向元素之前位置插入
    {
        assert(pos >= 0 && pos <= _size);
        Node *cur = head;
        while (pos != 0)
        {
            cur = cur->next;
            pos--;
        }
        Node *newnode = new Node(x);
        if(head==tail)
        {
            tail->next=newnode;
            tail=newnode;
        }
        else if(cur==tail)
        {
            cur->next=newnode;
            tail=newnode;
        }
        else
        {
            newnode->next=cur->next;
            cur->next = newnode;
        }
        _size++;
    }
    void push_back(const T &x)
    {
        /*Node *newnode = new Node(x);
        tail->next = newnode;
        tail = tail->next;
        _size++;*/
        insert(_size,x);
    }
    void push_front(const T &x)
    {
        /*Node *newnode = new Node(x);
        newnode->next = head->next;
        head->next = newnode;
        _size++;*/
        insert(0,x);
    }

    size_t find(T x) // 发现打印i+1，没有是0
    {
        Node *cur = head->next;
        int pos = 0;
        while (cur != nullptr)
        {
            pos++;
            if (cur->val == x)
            {
                return pos;
            }
            cur = cur->next;
        }
        return 0;
    }
    void erase(size_t pos) // 从head之后，head之后为0
    {
        assert(pos <= _size);
        Node *cur = head;
        while (pos--)
        {
            cur = cur->next;
        }
        Node *temp = cur->next;
        if (temp == tail)
        {
            tail = cur;
        }
        else
        {
            cur->next = cur->next->next;
        }
        free(temp);
        temp = nullptr;
        _size--;
    }
    void pop_back()
    {
        erase(_size - 1);
    }
    void PrintList()
    {
        Node *cur = head->next;
        while (cur != nullptr)
        {
            std::cout << cur->val << " ";
            cur = cur->next;
        }
        std::cout << std::endl;
    }
    size_t size()
    {
        return _size;
    }
    T &operator[](size_t i)
    {
        Node *cur = head->next;
        while (cur != nullptr && i != 0)
        {
            cur = cur->next;
            i--;
        }
        return cur->val;
    }
    void clear()
    {
        assert(_size > 0);
        int i = _size - 1;
        while (i >= 0)
        {
            erase(i);
            i--;
        }
        _size = 0;
        head->next = nullptr;
    }
    ~LinkList()
    {
    }

private:
    Node *head;
    Node *tail;
    size_t _size;
};
