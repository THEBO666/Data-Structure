#include <iostream>
#include <string>
#include "Graph1.hpp"

int main()
{
    /*Graph_Matrix<char,int,false> g1("ABCDEF",6);
    g1.addEdge('A','B',3);
    g1.addEdge('A','C',2);
    g1.addEdge('A','D',1);
    g1.addEdge('B','C',4);
    g1.addEdge('B','E',9);
    g1.addEdge('C','D',5);
    g1.addEdge('C','E',8);
    g1.addEdge('C','F',7);
    g1.addEdge('D','F',6);
    g1.addEdge('E','F',10);
    g1.Print();
    g1.BFS('F');
    g1.DFS('F');
    g1.Prim('A');
    g1.Dijkstra('A','F');*/
    Graph_Matrix<char, int> g("ABCD", 4);
    g.addEdge('A', 'B', 1);
    g.addEdge('A', 'C', 1);
    g.addEdge('B', 'D', 1);
    g.DFS('A');
    return 0;
}

