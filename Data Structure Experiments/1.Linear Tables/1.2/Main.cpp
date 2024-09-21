#include "LinkList.hpp"
#include <iostream>

int main()
{
    LinkList<char> lt;
    lt.push('z');
    lt.push('p');
    lt.push('o');
    lt.push('c');
    lt.push('a');
    lt.push('i');
    lt.push('5');
    lt.push('0');
    lt.PrintList();
    //lt.Delete_Interval(2,11);
    lt.PrintList();
    return 0;
}