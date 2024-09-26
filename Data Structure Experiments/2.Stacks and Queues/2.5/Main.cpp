#include <iostream>
#include <cstdio>

#include "Queue.hpp"

void solve(int m,int n,int k)
{
    Queue<int> man,woman;
    for(int i=1;i<=m;i++)
    {
        man.push(i);
    }
    for(int i=1;i<=n;i++)
    {
        woman.push(i);
    }
    
    printf("进行了%d轮匹配, 匹配结果如下:\n",k);
    for(int i=1;i<=k;i++)
    {
        printf("第%d轮匹配结果: (man%d, woman%d)\n",i,man.front(),woman.front());
        man.push(man.front());
        woman.push(woman.front());
        man.pop();
        woman.pop();
    }
    
}
int main()
{
    int m,n,k;
    std::cin>>m>>n>>k;
    solve(m,n,k);
    return 0;
}