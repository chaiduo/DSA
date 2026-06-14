// Prim Algorithm: Find Minimum Spanning Tree
// Time Complexity: O(n^2), suitable for dense graphs
// Core Idea: Each iteration add the vertex closest to the MST, update distances of other vertices
// Similar to Dijkstra, but dist maintains distance to MST instead of distance to source

#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, INF = 0x3f3f3f3f;
int n, m;
int g[N][N], dist[N];  // g is adjacency matrix, dist is shortest distance to MST
bool vis[N];

int prim()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;  // Virtual source with distance 0
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int t = -1;
        // Find unvisited vertex closest to MST
        for(int j = 1; j <= n; j++) 
            if(!vis[j] && (t == -1 || dist[j] < dist[t])) 
                t = j;

        if(i && dist[t] == INF) return INF;  // Graph is not connected
        ans += dist[t];
        
        vis[t] = true;
        // Update distances of other vertices to MST using t
        for(int j = 1; j <= n; j++) 
            dist[j] = min(dist[j], g[t][j]);
    }
    return ans;
}

int main()
{
    cin >> n >> m;
    memset(g, 0x3f, sizeof(g));
    while(m--) {
        int a, b, w;
        cin >> a >> b >> w;
        g[b][a] = g[a][b] = min(g[a][b], w);  // Undirected graph
    }
    
    int t = prim();
    if(t == INF) cout << "impossible";
    else cout << t << endl;
    return 0;
}