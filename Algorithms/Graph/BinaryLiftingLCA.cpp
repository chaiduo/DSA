// Binary Lifting for LCA (Lowest Common Ancestor)
// Preprocessing: O(n log n), Query: O(log n)
// Core Idea: Use fa[u][k] to record the 2^k-th ancestor of node u
// During query, first lift both nodes to same depth, then lift together using binary lifting

#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

const int N = 500010;

int root;
int dep[N], fa[N][20];  // dep: depth, fa[u][k]: 2^k-th ancestor of u
vector<int> edges[N];

// DFS to preprocess depth and binary lifting array
void dfs(int u, int v) {
    dep[u] = dep[v] + 1;
    fa[u][0] = v;  // Parent
    for(int k = 1; k <= 19; k++) 
        fa[u][k] = fa[fa[u][k - 1]][k - 1];  // Binary lifting recurrence
    for(int x : edges[u]) 
        if(x != v) dfs(x, u);
}

// Query LCA
int lca(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);  // Ensure a is deeper
    
    // Lift a to the same depth as b
    for(int k = 19; k >= 0; k--)
        if(dep[fa[a][k]] >= dep[b])
            a = fa[a][k];
            
    if(a == b) return b;  // b is ancestor of a
    
    // Lift both a and b until their parents are the same
    for(int k = 19; k >= 0; k--) 
        if(fa[a][k] != fa[b][k]) 
            a = fa[a][k], b = fa[b][k];
            
    return fa[a][0];  // Parent is the LCA
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