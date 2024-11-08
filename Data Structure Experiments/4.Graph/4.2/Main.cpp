#include <iostream>
#include "Graph2.hpp"
#include <string>

int main()
{
    std::string s1[4] = {"v0", "v1", "v2", "v3"};
    Graph_Link<std::string, int, true> g1(s1, 4);
    g1.addEdge("v0", "v1", 3);
    g1.addEdge("v0", "v3", 15);
    g1.addEdge("v1", "v2", 4);
    g1.addEdge("v1", "v3", 9);
    g1.addEdge("v2", "v3", 6);
    g1.Print();
    return 0;
}