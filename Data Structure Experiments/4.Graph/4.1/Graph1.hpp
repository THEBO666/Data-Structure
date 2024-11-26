#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
#include <algorithm>
/*
 *图的表示方式 G=(V,E) V是顶点 E是边
 *
 */
using namespace std;
template <class V, class W, bool Direction = false> // Direction为是否有向
class Graph_Matrix
{
    typedef Graph_Matrix<V, W, Direction> Self;

public:
    Graph_Matrix(const V *vertex, size_t n) // 初始化顶点
    {
        // _vertex.reserve(n);
        for (int i = 0; i < n; i++)
        {
            _vertex.push_back(vertex[i]);
            _vIndex[vertex[i]] = i;
        }
        // 初始化邻接矩阵
        _matrix.resize(n);
        for (auto &e : _matrix)
        {
            e.resize(n, INT_MAX);
        }
        for (int i = 0; i < n; i++)
        {
            _matrix[i][i] = 0;
        }
    }
    // 以邻接矩阵初始化
    Graph_Matrix(const std::vector<std::vector<W>> &m)
    {
        for (int i = 0; i < m.size(); i++)
        {
            for (int j = 0; j < m[0].size(); j++)
            {
                _matrix[i][j] = m[i][j];
            }
        }
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
        int srci = getVertexIndex(src);
        int dsti = getVertexIndex(dst);
        _matrix[srci][dsti] = w;
        if (Direction == false)
        {
            _matrix[dsti][srci] = w;
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
        std::cout << "邻接矩阵:\n";
        std::cout << "  ";
        for (size_t i = 0; i < _vertex.size(); ++i)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        // 打印邻接矩阵
        for (size_t i = 0; i < _matrix.size(); ++i)
        {
            std::cout << i << " ";
            for (size_t j = 0; j < _matrix[i].size(); ++j)
            {
                if (_matrix[i][j] != INT_MAX)
                    std::cout << _matrix[i][j] << " ";
                else
                    std::cout << "#" << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        // 打印所有的边
        std::cout << "所有边的情况:\n";
        for (size_t i = 0; i < _matrix.size(); ++i)
        {
            for (size_t j = 0; j < _matrix[i].size(); ++j)
            {
                if (i != j && _matrix[i][j] != INT_MAX)
                {
                    std::cout << _vertex[i] << "-" << _vertex[j] << ":" << _matrix[i][j] << "  ";
                }
            }
            std::cout << std::endl;
        }
        // 打印每个顶点的度
        std::cout << "\n所有顶点的度:\n";
        if (Direction == false) // 无向图
        {
            for (int i = 0; i < _vertex.size(); i++)
            {
                int degree = 0;
                for (int j = 0; j < _vertex.size(); j++)
                {
                    if (_matrix[i][j] != INT_MAX && i != j)
                    {
                        degree++;
                    }
                }
                std::cout << "顶点 " << _vertex[i] << " 的度为 " << degree << std::endl;
            }
        }
        else // 有向图
        {
            for (int i = 0; i < _vertex.size(); i++)
            {
                int in_degree = 0;
                int out_degree = 0;
                for (int j = 0; j < _vertex.size(); j++)
                {
                    if (_matrix[j][i] != INT_MAX && j != i)
                    {
                        in_degree++;
                    }
                    if (_matrix[i][j] != INT_MAX && i != j)
                    {
                        out_degree++;
                    }
                }
                std::cout << "顶点 " << _vertex[i] << " 的入度为 " << in_degree << "，出度为 " << out_degree << std::endl;
            }
        }
        std::cout << std::endl;
    }
    void BFS(const V &src) // 从哪一个开始BFS
    {
        int srci = getVertexIndex(src);
        std::vector<bool> visited(_vertex.size(), false);
        std::queue<int> q;
        std::cout << "The graph from point " << _vertex[srci] << "'s BFS: " << std::endl;
        q.push(srci);
        visited[srci] = true;
        std::cout << srci << src << " ";
        while (!q.empty())
        {
            int font = q.front();
            q.pop();
            for (int i = 0; i < _vertex.size(); i++)
            {
                if (_matrix[font][i] != INT_MAX && visited[i] == false)
                {
                    visited[i] = true;
                    std::cout << i << _vertex[i] << " ";
                    q.push(i);
                }
            }
            // std::cout << std::endl;
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
        if (Direction)
        {
            std::cerr << "Prim's algorithm is not applicable to directed graphs." << std::endl;
            return;
        }
        int srci = getVertexIndex(src);
        std::vector<W> minWeight(_vertex.size(), INT_MAX);
        std::vector<int> parent(_vertex.size(), -1); // 记录最小生成树的双亲节点
        std::vector<bool> visited(_vertex.size(), false);
        minWeight[srci] = 0;
        // 使用优先队列优化，greater是变小堆
        std::priority_queue<std::pair<W, int>, std::vector<std::pair<W, int>>, std::greater<std::pair<W, int>>> pq;
        pq.push({minWeight[srci], srci});
        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            if (visited[u])
                continue;
            visited[u] = true;
            for (int i = 0; i < _vertex.size(); i++)
            {
                if (_matrix[u][i] != INT_MAX && !visited[i] && _matrix[u][i] < minWeight[i])
                {
                    minWeight[i] = _matrix[u][i]; // 更新
                    parent[i] = u;
                    pq.push({minWeight[i], i});
                }
            }
        }
        std::cout << "Prim's MST from " << src << ": " << "\n";
        for (int i = 0; i < _vertex.size(); i++)
        {
            if (parent[i] != -1)
            {
                std::cout << _vertex[parent[i]] << " - " << _vertex[i] << " : " << _matrix[parent[i]][i] << "\n";
            }
        }
        std::cout << std::endl;
    }
    W Dijkstra(const V &src, const V &dst)
    {
        int srci = getVertexIndex(src);
        int dsti = getVertexIndex(dst);
        std::vector<W> dist(_vertex.size(), INT_MAX);
        std::vector<int> parent(_vertex.size(), -1); // 记录路径
        std::vector<bool> visited(_vertex.size(), false);
        dist[srci] = 0;

        // 使用优先队列优化，greater是变小堆
        std::priority_queue<std::pair<W, int>, std::vector<std::pair<W, int>>, std::greater<std::pair<W, int>>> pq;
        pq.push({dist[srci], srci});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            if (visited[u])
                continue;
            visited[u] = true;

            for (int i = 0; i < _vertex.size(); i++)
            {
                if (_matrix[u][i] != INT_MAX && !visited[i] && dist[u] + _matrix[u][i] < dist[i])
                {
                    dist[i] = dist[u] + _matrix[u][i]; // 与prime算法的区别
                    parent[i] = u;
                    pq.push({dist[i], i});
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
        std::cout << srci << _vertex[srci] << " ";
        visited[srci] = true;
        for (int i = 0; i < _vertex.size(); i++)
        {
            if (visited[i] == false && _matrix[srci][i] != INT_MAX)
            {
                _DFS(i, visited);
            }
        }
    }
    // std::vector<std::pair<V,int>> _vIndex;
    std::unordered_map<V, int> _vIndex;  // 下标索引
    std::vector<V> _vertex;              // 顶点
    std::vector<std::vector<W>> _matrix; // 矩阵存储
};
