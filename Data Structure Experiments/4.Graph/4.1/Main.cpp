#include <iostream>
#include "Graph1.hpp"

int main()
{
    Graph_Matrix<char,int,false> g1("ABCD",4);
    g1.addEdge('A','B',1);
    g1.addEdge('B','C',3);
    g1.addEdge('A','C',2);
    g1.addEdge('B','D',3);
    g1.addEdge('C','D',1);
    g1.Print();
    g1.BFS('A');
    return 0;
}