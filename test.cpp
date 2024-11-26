#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <climits>
using namespace std;

struct Graph {
    Graph(int n) {
        matrix.resize(n);
        for (auto &e : matrix) {
            e.resize(n, INT_MAX);
        }
    }
    void addEdge(const int src, const int dst, int val) {
        matrix[src][dst] = matrix[dst][src] = val;
    }
    void solve(int src, int dst) {
        int n = matrix.size();
        vector<int> dist(n, INT_MAX);
        vector<int> rescue(n, 0);
        vector<int> pathCount(n, 0);
        vector<bool> visited(n, false);
        vector<int> prev(n, -1); // 用于记录路径
        dist[src] = 0;
        rescue[src] = nums[src];
        pathCount[src] = 1;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (int v = 0; v < n; ++v) {
                if (matrix[u][v] != INT_MAX && !visited[v]) {
                    if (dist[u] + matrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + matrix[u][v];
                        rescue[v] = rescue[u] + nums[v];
                        pathCount[v] = pathCount[u];
                        pq.push({dist[v], v});
                        prev[v] = u; // 记录路径
                    } else if (dist[u] + matrix[u][v] == dist[v]) {
                        if (rescue[u] + nums[v] > rescue[v]) {
                            rescue[v] = rescue[u] + nums[v];
                            prev[v] = u; // 更新路径
                        }
                        pathCount[v] += pathCount[u];
                    }
                }
            }
        }

        cout << pathCount[dst] << " " << rescue[dst] << endl;

        // 输出路径
        vector<int> path;
        for (int v = dst; v != -1; v = prev[v]) {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());
        for (int i = 0; i < path.size(); ++i) {
            if (i > 0) cout << " ";
            cout << path[i];
        }
        cout << endl;
    }
    vector<vector<int>> matrix;
    vector<int> nums;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, s, d;
    while (cin >> n >> m >> s >> d) {
        Graph g(n);
        for (int i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            g.nums.push_back(temp);
        }
        for (int i = 0; i < m; i++) {
            int src, dst, val;
            cin >> src >> dst >> val;
            g.addEdge(src, dst, val);
        }
        g.solve(s, d);
    }

    return 0;
}