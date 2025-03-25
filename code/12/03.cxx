#include <bits/stdc++.h>
using namespace std;

struct UnionFind {
    vector<int> parent;
    UnionFind(int n) : parent(n) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x != y) {
            parent[y] = x;
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    UnionFind uf(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        uf.unite(u, v);
    }

    vector<int> color(n, -1);
    vector<bool> is_bipartite(n, true);
    vector<bool> visited(n, false);

    for (int u = 0; u < n; ++u) {
        int root = uf.find(u);
        if (visited[root]) continue;
        visited[root] = true;
        queue<int> q;
        q.push(root);
        color[root] = 0;
        bool bipart_ok = true;
        vector<int> component;
        component.push_back(root);
        while (!q.empty() && bipart_ok) {
            int v = q.front();
            q.pop();
            for (int neighbor : adj[v]) {
                if (uf.find(neighbor) != root) {
                    continue;
                }
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    color[neighbor] = color[v] ^ 1;
                    component.push_back(neighbor);
                    q.push(neighbor);
                } else {
                    if (color[neighbor] == color[v]) {
                        bipart_ok = false;
                        break;
                    }
                }
            }
        }
        for (int node : component) {
            is_bipartite[node] = bipart_ok;
            if (!bipart_ok) {
                color[node] = -1;
            }
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int u, v, p, qq;
        cin >> u >> v >> p >> qq;
        --u; --v;
        if (uf.find(u) != uf.find(v)) {
            cout << "no\n";
            continue;
        }
        if (!is_bipartite[uf.find(u)]) {
            cout << "yes\n";
        } else {
            int desired = (qq - p) % 2;
            if (desired < 0) desired += 2;
            int actual = (color[u] != color[v]) ? 1 : 0;
            if (desired == actual) {
                cout << "yes\n";
            } else {
                cout << "no\n";
            }
        }
    }

    return 0;
}