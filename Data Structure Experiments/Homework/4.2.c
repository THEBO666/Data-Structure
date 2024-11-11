#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 50

#define INF 0x7fffffff

typedef struct GraphData
{
    int data[MAX_LEN][MAX_LEN];
    int v; // 度数
} Graph;

void addEdge(Graph *g, const int src, const int dst, int w)
{
    g->data[dst][src] = g->data[src][dst] = w;
}

int min(int a, int b)
{
    return a > b ? b : a;
}

// Prim算法求解
int Prim(Graph g)
{
    bool visited[MAX_LEN];
    memset(visited, 0, sizeof(visited));
    int dist[MAX_LEN];
    for (int i = 0; i <= g.v; i++)
        dist[i] = INF;
    int res = 0;
    dist[1] = 0;
    visited[1] = true;
    for (int i = 2; i <= g.v; i++)
        dist[i] = min(dist[i], g.data[1][i]);
    for (int i = 2; i <= g.v; i++)
    {
        int temp = INF;
        int flag = -1;
        for (int j = 2; j <= g.v; j++)
        {
            if (!visited[j] && dist[j] < temp)
            {
                temp = dist[j];  //寻找最小的dist[j]
                flag = j;
            }
        }
        if (flag == -1)
            return 0;
        visited[flag] = true;
        res += dist[flag];
        for (int j = 2; j <= g.v; j++)
            dist[j] = min(dist[j], g.data[flag][j]);
    }
    return res;
}

int main()
{
    Graph g;

    int n, m;
    scanf("%d %d", &n, &m);
    g.v = n;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            g.data[i][j] = INF;
        }
    }

    while (m--)
    {
        int src, dst, w; // 源点、目标、权值
        scanf("%d%d%d", &src, &dst, &w);
        addEdge(&g, src, dst, w);
        //g.data[dst][src] = g.data[src][dst] = w;
    }
    // 从1开始
    int res = Prim(g);
    printf("%d\n", res);
    return 0;
}