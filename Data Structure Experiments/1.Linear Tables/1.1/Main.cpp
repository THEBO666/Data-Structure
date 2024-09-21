#include "Sqlist.hpp"
#include "LinkList.hpp"
#include <iostream>


int main()
{
    /*Sqlist<int> sq;
    sq.InitSqlist();
    sq.push_back(1);
    sq.push_back(2);
    sq.push_back(3);
    sq.push_back(4);
    sq.push_back(5);
    sq.push_back(6);
    sq.push_back(9);
    sq.insert(6,999);
    sq.erase(7);
    for(int i=0;i<sq.size();i++)
    {
        std::cout<<sq[i]<<" ";
    }
    std::cout<<sq.find(6);*/
    LinkList<int> lt;
    lt.push_back(1);
    lt.push_back(2);
    lt.push_back(3);
    lt.push_back(4);
    lt.push_back(5);
    lt.PrintList();
    lt.insert(1,99);
    lt.PrintList();
    std::cout<<lt.size();
    return 0;
    

}