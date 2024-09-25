#include <iostream>
#include "List.hpp"

int main()
{
    int n, m;
    std::cin >> n >> m;
    List<int> st;
    st.Josephus(n, m);
    return 0;
}