#include <iostream>
#include "Graph2.hpp"
#include <string>

int main()
{
    /*Graph_Link<char, int, true> g1("ABCEF", 5);
    g1.addEdge('A', 'B', 15);
    g1.addEdge('A', 'E', 9);
    g1.addEdge('B', 'C', 3);
    g1.addEdge('C', 'F', 2);
    g1.addEdge('F', 'A', 11);
    g1.addEdge('F', 'B', 7);
    g1.addEdge('E', 'C', 21);
    g1.Print();
    g1.BFS('A');
    g1.DFS('A');
    g1.Prim('A');
    g1.Dijkstra('A', 'F');*/
    Graph_Link<char, int, false> g1("ABCD", 5);
    g1.addEdge('A','B',1);
    g1.addEdge('B','C',1);
    g1.addEdge('B','D',1);
    g1.addEdge('C','D',1);
    g1.Print();
    return 0;
}
