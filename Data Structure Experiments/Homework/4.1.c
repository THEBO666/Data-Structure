#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 50 

void DFS(int g[][MAX_LEN], bool visited[], int i, int n)
{
    visited[i] = 1;
    for (int j = 0; j < n; j++)
    {
        if (g[i][j] == 1 && !visited[j])
        {
            DFS(g, visited, j, n);
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int Graph[MAX_LEN][MAX_LEN];
    bool visited[MAX_LEN];
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &Graph[i][j]);
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            cnt++;
            DFS(Graph, visited, i, n);
        }
    }
    printf("%d\n", cnt);
    return 0;
}
