// Tarjan Offline LCA Algorithm
// Time Complexity: O(n + m), process all queries at once
// Core Idea: During DFS, the LCA of visited nodes is their root in Union-Find
// For query (u, v), when DFS reaches u, the LCA of all visited v is find(v)

#include <iostream>
#include <vector>
using namespace std;

const int N = 100010, M = 100010;
typedef pair<int, int> PII;

bool vis[N];
int ans[M], dist[N], p[N];  // p: Union-Find parent
vector<int> edges[N];
vector<PII> query[N];  // Store queries offline

int find(int x) {
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
}

void tarjan(int u) {
    vis[u] = true;
    for(int v: edges[u]) {
        if(!vis[v]) {
            tarjan(v);
            p[v] = u;  // After backtracking, set v's Union-Find parent to u
        }
    }
    
    // Process all queries related to u
    for(auto [v, i]: query[u]) {
        if(vis[v]) ans[i] = find(v);  // v has been visited, LCA is find(v)
    }
}
int main()
{
    int n, m, root;
    cin >> n >> m >> root;
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        query[x].push_back({y, i});
        query[y].push_back({x, i});
    }
    for(int i = 0; i <= n; i++) p[i] = i;

    tarjan(root);
    
    for(int i = 0; i < m; i++) cout << ans[i] << endl;
    return 0;
}


