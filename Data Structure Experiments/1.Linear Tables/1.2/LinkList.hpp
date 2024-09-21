#pragma once

#include <iostream>
#include <cassert>
#include <algorithm>

template <class T>
struct ListNode
{
    T val;
    ListNode *next;
    ListNode() {}
    ListNode(const T &a) : val(a), next(nullptr) {}
};

template <class T>
class LinkList
{
    typedef ListNode<T> Node;

public:
    LinkList() : _size(0)
    {
        head = new Node(0);
        head->next = head;
        tail = head;
    }
    void push(T x) // 这里插入尾插，可以调节链表有序
    {
        Node *cur = head;
        int pos = 0;
        bool isInsert = false;
        if (_size == 0)
        {
            Node *newnode = new Node(x);
            cur->next = newnode;
            _size++;
        }
        else
        {
            while (cur->next != nullptr)
            {
                if (cur->next->val > x)
                {
                    insert(pos, x);
                    isInsert = true;
                    break;
                }
                pos++;
                cur = cur->next;
            }
            if (!isInsert)
            {
                insert(pos, x);
            }
        }
    }
    void insert(int pos, T x) // 从head之后开始，开始为0，向元素之后位置插入
    {
        Node *cur = head;
        while (pos != 0)
        {
            cur = cur->next;
            pos--;
        }
        Node *newnode = new Node(x);
        newnode->next = cur->next;
        cur->next = newnode;
        _size++;
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
        assert(pos <= _size - 1);
        Node *cur = head;
        while (pos--)
        {
            cur = cur->next;
        }
        Node *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
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
    void Delete_Interval(int min, int max)
    {
        Node *cur=head->next;
        while(cur->next!=nullptr)
        {
            T data=cur->next->val;
            if(data>=min&&data<=max)
            {
                Node *temp=cur->next;
                cur->next=cur->next->next;
                delete temp;
            }
            if(data>max)
                break;
        }

    }
    size_t size()
    {
        return _size;
    }
    void clear()
    {
    }
    ~LinkList()
    {
    }

private:
    Node *head;
    Node *tail;
    size_t _size;
};
