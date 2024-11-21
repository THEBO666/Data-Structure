#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
template <class W>
struct LinkEdge
{
    int _dstIndex;
    LinkEdge<W> *next;
    W _w;
    LinkEdge(int dsti, const W &w) : _dstIndex(dsti), _w(w), next(nullptr)
    {
    }
};

template <class V, class W, bool Direction = false>
class Graph_Link
{
    typedef LinkEdge<W> Edge;

public:
    Graph_Link(const V *vertex, int n)
    {
        for (int i = 0; i < n; i++)
        {
            _vertex.push_back(vertex[i]);
            _vIndex[vertex[i]] = i;
        }
        _linkTable.resize(n, nullptr);
    }
    int getVertexIndex(const V &v)
    {
        auto ret = _vIndex.find(v);
        if (ret != _vIndex.end())
        {
            return ret->second;
        }
        else
        {
            std::cerr << "error, don't have this vertex\n";
            return 0;
        }
    }
    void addEdge(const V &src, const V &dst, const W &w)
    {
        int dsti = getVertexIndex(dst);
        int srci = getVertexIndex(src);
        Edge *eg = new Edge(dsti, w);
        eg->next = _linkTable[srci]; // 头插，初始化的边表都是空指针，便于节省空间
        _linkTable[srci] = eg;
        if (Direction == false)
        {
            Edge *eg1 = new Edge(srci, w);
            eg1->next = _linkTable[dsti];
            _linkTable[dsti] = eg1;
        }
    }
    void Print()
    {
        // 打印顶点和下标映射关系
        std::cout << "顶点和下标映射关系: ";
        for (size_t i = 0; i < _vertex.size(); i++)
        {
            std::cout << _vertex[i] << "-" << i << " ";
        }
        std::cout << std::endl
                  << std::endl;
        std::cout << "邻接表表示: \n";
        for (size_t i = 0; i < _linkTable.size(); ++i)
        {
            std::cout << _vertex[i] << "[" << i << "]->";
            Edge *cur = _linkTable[i];
            while (cur)
            {
                std::cout << "[" << _vertex[cur->_dstIndex] << ":" << cur->_dstIndex << ":" << cur->_w << "]->";
                cur = cur->next;
            }
            std::cout << "nullptr" << std::endl;
        }
        std::cout << std::endl;
        // 打印所有顶点的度:
        std::cout << "所有顶点的度:\n";
        if (Direction == false) // 无向图的度
        {
            for (size_t i = 0; i < _vertex.size(); ++i)
            {
                int degree = 0;
                Edge *cur = _linkTable[i];
                while (cur)
                {
                    degree++;
                    cur = cur->next;
                }
                std::cout << "顶点 " << _vertex[i] << " 的度为 " << degree << std::endl;
            }
        }
        else // 有向图的度，入度、出度
        {
            // 计算每个顶点的入度
            std::vector<int> in_degree(_vertex.size(), 0);
            for (size_t i = 0; i < _linkTable.size(); ++i)
            {
                Edge *cur = _linkTable[i];
                while (cur)
                {
                    in_degree[cur->_dstIndex]++;
                    cur = cur->next;
                }
            }
            // 打印每个顶点的入度和出度
            for (size_t i = 0; i < _vertex.size(); ++i)
            {
                int out_degree = 0;
                Edge *cur = _linkTable[i];
                while (cur)
                {
                    out_degree++;
                    cur = cur->next;
                }
                std::cout << "顶点 " << _vertex[i] << " 的入度为 " << in_degree[i] << "，出度为 " << out_degree << std::endl;
            }
        }
        std::cout << std::endl;
    }

    void BFS(const V &src)
    {
        int srci = getVertexIndex(src);
        std::vector<bool> visited(_vertex.size(), false);
        std::queue<int> q;
        std::cout << "The graph from point " << _vertex[srci] << "'s BFS: " << std::endl;
        q.push(srci);
        visited[srci] = true;
        while (!q.empty())
        {
            int font = q.front();
            q.pop();
            std::cout << _vertex[font] << " ";
            for (Edge *cur = _linkTable[font]; cur != nullptr; cur = cur->next)
            {
                if (!visited[cur->_dstIndex])
                {
                    visited[cur->_dstIndex] = true;
                    q.push(cur->_dstIndex);
                }
            }
        }
        std::cout << std::endl
                  << std::endl;
    }
    void DFS(const V &src)
    {
        int srci = getVertexIndex(src);
        std::cout << "The graph from point " << _vertex[srci] << "'s DFS: " << std::endl;
        std::vector<bool> visited(_vertex.size(), false);
        _DFS(srci, visited);
        std::cout << std::endl
                  << std::endl;
    }
    void Prim(const V &src)
    {
        int srci = getVertexIndex(src);
        std::vector<W> key(_vertex.size(), INT_MAX);
        std::vector<int> parent(_vertex.size(), -1);
        std::vector<bool> inMST(_vertex.size(), false);
        key[srci] = 0;

        for (int count = 0; count < _vertex.size() - 1; ++count)
        {
            // 找到不在MST中且key值最小的顶点
            int u = -1;
            W minKey = INT_MAX;
            for (int i = 0; i < _vertex.size(); ++i)
            {
                if (!inMST[i] && key[i] < minKey)
                {
                    minKey = key[i];
                    u = i;
                }
            }

            if (u == -1)
                break; // 如果没有找到，跳出循环

            inMST[u] = true;

            // 更新邻接节点的key值
            for (Edge *cur = _linkTable[u]; cur != nullptr; cur = cur->next)
            {
                if (!inMST[cur->_dstIndex] && cur->_w < key[cur->_dstIndex])
                {
                    key[cur->_dstIndex] = cur->_w;
                    parent[cur->_dstIndex] = u;
                }
            }
        }

        // 打印最小生成树
        std::cout << "Prim's MST starting from " << src << ": " << std::endl;
        for (int i = 0; i < _vertex.size(); ++i)
        {
            if (i != srci && parent[i] != -1)
            {
                std::cout << _vertex[parent[i]] << " - " << _vertex[i] << " : " << key[i] << std::endl;
            }
        }
        std::cout<<std::endl;
    }
    W Dijkstra(const V &src, const V &dst)
    {
        int srci = getVertexIndex(src);
        int dsti = getVertexIndex(dst);
        std::vector<W> dist(_vertex.size(), INT_MAX);
        std::vector<int> parent(_vertex.size(), -1); // 记录路径
        std::vector<bool> visited(_vertex.size(), false);
        dist[srci] = 0;

        for (int i = 0; i < _vertex.size() - 1; i++)
        {
            // 找到未访问结点距离最小值
            int flag = -1;
            W minDist = INT_MAX;
            for (int j = 0; j < _vertex.size(); j++)
            {
                if (!visited[j] && dist[j] < minDist)
                {
                    minDist = dist[j];
                    flag = j;
                }
            }
            if (flag == -1)
                break;
            visited[flag] = true;
            for (Edge *cur = _linkTable[flag]; cur != nullptr; cur = cur->next)
            {
                if (!visited[cur->_dstIndex] && dist[flag] + cur->_w < dist[cur->_dstIndex])
                {
                    dist[cur->_dstIndex] = dist[flag] + cur->_w;
                    parent[cur->_dstIndex] = flag;
                }
            }
        }

        // 打印路径
        std::cout << "Dijkstra's shortest path from " << src << " to " << dst << ": ";
        if (dist[dsti] == INT_MAX)
        {
            std::cout << "No path found." << std::endl;
            return INT_MAX;
        }

        std::vector<int> path;
        for (int v = dsti; v != -1; v = parent[v])
        {
            path.push_back(v);
        }
        std::reverse(path.begin(), path.end());

        for (int i = 0; i < path.size(); ++i)
        {
            std::cout << _vertex[path[i]];
            if (i != path.size() - 1)
            {
                std::cout << " -> ";
            }
        }
        std::cout << std::endl;
        return dist[dsti];
    }

private:
    void _DFS(int srci, std::vector<bool> &visited)
    {
        visited[srci] = true;
        std::cout << _vertex[srci] << " ";
        for (Edge *cur = _linkTable[srci]; cur != nullptr; cur = cur->next)
        {
            if (!visited[cur->_dstIndex])
                _DFS(cur->_dstIndex, visited);
        }
    }
    std::unordered_map<V, int> _vIndex;
    std::vector<V> _vertex;
    std::vector<Edge *> _linkTable;
};