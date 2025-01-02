#include <iostream>
#include <stdio.h>

using namespace std;
typedef struct HuffmanNode
{
    int weight;
    int parent;
    int lc, rc;
} *HuffmanTree;
void Select(HuffmanTree &HT, int n, int &s1, int &s2)
{
    int min;
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0)
        {
            min = i;
            break;
        }
    }
    for (int i = min + 1; i <= n; i++)
    {
        if (HT[i].parent == 0 && HT[i].weight < HT[min].weight)
            min = i;
    }
    s1 = min;
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].parent == 0 && i != s1)
        {
            min = i;
            break;
        }
    }
    for (int i = min + 1; i <= n; i++)
    {
        if (HT[i].parent == 0 && HT[i].weight < HT[min].&& i != s1)
            min = i;
    }
    s2 = min;
}

void CreateHuff(HuffmanTree &HT, int *w, int n)
{
    int m = 2 * n - 1;
    HT = (HuffmanTree)calloc(m + 1, sizeof(HuffmanNode));
    for (int i = 1; i <= n; i++)
    {
        HT[i].weight = w[i - 1];
    }
    for (int i = n + 1; i <= m; i++)
    {
        int s1, s2;
        Select(HT, i - 1, s1, s2);
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lc = s1;
        HT[i].rc = s2;
    }
}
int main()
{
    return 0;
}