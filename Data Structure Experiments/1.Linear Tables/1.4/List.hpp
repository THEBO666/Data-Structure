#include <iostream>
#include <cassert>
#include <cstdio>

template <class T>
struct Node
{
    int data;
    Node *next;
    Node *prev;
    Node() {}
    Node(T d) : data(d), next(nullptr), prev(nullptr) {}
};

template <class T>
class List
{
    typedef Node<T> Node;

public:
    List() : head(nullptr), size(0) {} // Initialize size to 0
    void push_back(T x)
    {
        Node *newnode = new Node(x);
        if (!head)
        {
            head = newnode;
            head->next = head;
            head->prev = head;
        }
        else
        {
            Node *tail = head->prev;
            tail->next = newnode;
            newnode->next = head;
            newnode->prev = tail;
            head->prev = newnode;
        }
        size++;
    }
    void erase(Node *node)
    {
        assert(size != 0);
        if (node == head)
        {
            if (node->next == node)
            {
                node = nullptr;
            }
            else
            {

                node->next->prev = node->prev;
                node->prev->next = node->next;
                head = node->next;
            }
        }
        else
        {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        delete node;
        node = nullptr;
        size--;
    }

    void Josephus(int n, int m)
    {
        for (int i = 1; i <= n; i++)
            push_back(i);
        Node *current = head;
        int count = 0;
        printf("(%d,%d)的Josephus排列为:", n, m);
        while (current != nullptr)
        {
            if (size == 1)
            {
                std::cout << current->data;
                break;
                erase(current);
            }
            count++;
            if (m % 2 == 1)
            {
                current = current->next;
            }
            else
            {
                current = current->prev;
            }
            if (count == m)
            {
                Node *temp = (m % 2 == 1) ? current->prev : current->next;
                std::cout << temp->data << " ";
                erase(temp);
                count = 0;
            }
        }
        std::cout << std::endl;
    }

private:
    Node *head;
    int size;
};
