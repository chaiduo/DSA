// Tarjan 离线 LCA 算法
// 时间复杂度 O(n + m)，一次性处理所有查询
// 核心思想：DFS 过程中，已访问的节点的最近公共祖先就是其在并查集中的根
// 对于查询 (u, v)，当 DFS 到 u 时，所有已访问的 v 的 LCA 就是 find(v)

#include <iostream>
#include <vector>
using namespace std;

const int N = 100010, M = 100010;
typedef pair<int, int> PII;

bool vis[N];
int ans[M], dist[N], p[N];  // p: 并查集父节点
vector<int> edges[N];
vector<PII> query[N];  // 离线存储查询

int find(int x) {
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
}

void tarjan(int u) {
    vis[u] = true;
    for(int v: edges[u]) {
        if(!vis[v]) {
            tarjan(v);
            p[v] = u;  // 回溯后将 v 的并查集父节点设为 u
        }
    }
    
    // 处理与 u 相关的所有查询
    for(auto [v, i]: query[u]) {
        if(vis[v]) ans[i] = find(v);  // v 已访问，LCA 为 find(v)
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


