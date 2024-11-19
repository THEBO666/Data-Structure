#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <string>
/*
 *图的表示方式 G=(V,E) V是顶点 E是边
 *
 */
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
        std::cout << "所有顶点的度:\n";
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
    }
    void BFS(const V &src) // 从哪一个开始BFS
    {
        int srci = getVertexIndex(src);
        std::vector<bool> visited(_vertex.size(), false);
        std::queue<int> q;
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
            std::cout << std::endl;
        }
    }

    void DFS(const V &src)
    {
    }

    W Prim()
    {
        if (Direction)
        {
            std::cerr << "Prim's algorithm is not applicable to directed graphs." << std::endl;
            return W();
        }

        int n = _vertex.size();
        std::vector<W> key(n, INT_MAX);
        std::vector<int> parent(n, -1);
        std::vector<bool> inMST(n, false);

        key[0] = 0;
        W totalWeight = 0;

        for (int count = 0; count < n - 1; count++)
        {
            int u = minKey(key, inMST);
            inMST[u] = true;

            for (int v = 0; v < n; v++)
            {
                if (_matrix[u][v] != INT_MAX && inMST[v] == false && _matrix[u][v] < key[v])
                {
                    key[v] = _matrix[u][v];
                    parent[v] = u;
                }
            }
        }

        std::cout << "Edges in MST:\n";
        for (int i = 1; i < n; i++)
        {
            std::cout << _vertex[parent[i]] << " - " << _vertex[i] << " : " << _matrix[i][parent[i]] << std::endl;
            totalWeight += _matrix[i][parent[i]];
        }

        return totalWeight;
    }
    int minKey(const std::vector<W> &key, const std::vector<bool> &inMST)
    {
        W min = INT_MAX;
        int min_index;

        for (int v = 0; v < key.size(); v++)
        {
            if (inMST[v] == false && key[v] < min)
            {
                min = key[v];
                min_index = v;
            }
        }

        return min_index;
    }

private:
    // std::vector<std::pair<V,int>> _vIndex;
    std::unordered_map<V, int> _vIndex;  // 下标索引
    std::vector<V> _vertex;              // 顶点
    std::vector<std::vector<W>> _matrix; // 矩阵存储
};
