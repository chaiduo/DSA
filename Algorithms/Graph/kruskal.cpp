// Kruskal Algorithm: Find Minimum Spanning Tree
// Time Complexity: O(m log m)
// Core Idea: Greedy approach, sort edges by weight in ascending order, add edges that don't form a cycle
// Use Union-Find to detect cycles

#include <iostream>
#include <algorithm>
using namespace std;

const int M = 2e5, N = 1e5;
struct Edge {
    int a, b, w;
} edge[M];
int n, m;
int f[N];

int find(int x) {
    if(f[x] == x) return x;
    return f[x] = find(f[x]);  // Path compression
}

int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edge[i] = {a, b, w};
    }
    // Sort edges by weight in ascending order
    sort(edge, edge + m, [&](auto t1, auto t2) {
        return t1.w < t2.w;
    });
    
    for(int i = 1; i <= n; i++) f[i] = i;  // Initialize Union-Find
    
    int ans = 0, cnt = 0;
    for(int i = 0; i < m; i++) {
        int a = find(edge[i].a);
        int b = find(edge[i].b);
        if(a != b) {  // Not in the same set, add this edge
            ans += edge[i].w;
            f[a] = b;
            cnt++;
        }
        if(cnt == n - 1) break;  // Already selected n-1 edges
    }
    if(cnt < n - 1) cout << "impossible";  // Graph is not connected
    else cout << ans;
    return 0;
}