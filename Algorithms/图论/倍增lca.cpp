// 倍增法求 LCA（最近公共祖先）
// 预处理 O(n log n)，每次查询 O(log n)
// 核心思想：用 fa[u][k] 记录节点 u 的第 2^k 级祖先
// 查询时先将两点调到同一深度，再同时向上倍增

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 500010;

int root;
int dep[N], fa[N][20];  // dep: 深度, fa[u][k]: u 的第 2^k 级祖先
vector<int> edges[N];

// DFS 预处理深度和倍增数组
void dfs(int u, int v) {
    dep[u] = dep[v] + 1;
    fa[u][0] = v;  // 父亲
    for(int k = 1; k <= 19; k++) 
        fa[u][k] = fa[fa[u][k - 1]][k - 1];  // 倍增递推
    for(int x : edges[u]) 
        if(x != v) dfs(x, u);
}

// 查询 LCA
int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);  // 保证 a 更深
    
    // 将 a 上提到与 b 同一深度
    for(int k = 19; k >= 0; k--)
        if(dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
            
    if(a == b) return b;  // b 是 a 的祖先
    
    // 同时上提 a 和 b，直到它们的父亲相同
    for(int k = 19; k >= 0; k--) 
        if(fa[a][k] != fa[b][k]) 
            a = fa[a][k], b = fa[b][k];
            
    return fa[a][0];  // 父亲即为 LCA
}
int main()
{
    int n, m, root;
    scanf("%d%d%d", &n, &m, &root);
    cin >> n >> m >> root;
    for(int i = 1, a, b; i < n; i++) {
        scanf("%d%d", &a, &b);
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    dfs(root, 0);
    for(int i = 0, a, b; i < m; i++) {
        scanf("%d%d", &a, &b);
        cout << lca(a, b) << endl;
    }
    return 0;
}