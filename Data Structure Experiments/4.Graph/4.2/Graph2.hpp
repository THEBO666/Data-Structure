#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

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
    }

private:
    std::unordered_map<V, int> _vIndex;
    std::vector<V> _vertex;
    std::vector<Edge *> _linkTable;
};