#include <iostream>
#include "Graph1.hpp"

int main()
{
    Graph_Matrix<char,int,true> g1("ABC",3);
    g1.addEdge('A','B',5);
    g1.addEdge('A','C',3);
    g1.addEdge('A','D',2);
    g1.addEdge('B','C',3);
    g1.addEdge('C','D',1);
    g1.Print();
    g1.BFS('A');
    return 0;
}