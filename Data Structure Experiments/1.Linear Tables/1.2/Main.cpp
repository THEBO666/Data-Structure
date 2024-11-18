#include "LinkList.hpp"
#include <iostream>

int main()
{
    LinkList<int> lt;
    lt.push(18);
    lt.push(12);
    lt.push(10);
    lt.push(19);
    lt.push(11);
    lt.push(20);
    lt.push(30);
    lt.push(15);
    lt.push(17);
    lt.push(23);
    lt.PrintList();
    lt.Delete_Interval(10,30);
    lt.PrintList();
    return 0;
}