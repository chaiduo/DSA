// Dijkstra Algorithm (Naive Version): Find Single-Source Shortest Path (Dense Graph)
// Time Complexity: O(n^2), suitable for dense graphs (adjacency matrix storage)
// Core Idea: Each iteration select unvisited node with minimum distance, update its neighbors
// Cannot handle negative weight edges

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
int n, m;
const int N = 510, M = 100010;
const int INF = 0x3f3f3f3f;
int g[N][N], dist[N];  // g is adjacency matrix, dist is distance from source
bool vis[N];

int Dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;    
    // Iterate n-1 times, each time determine shortest path for one node
    for(int i = 1; i <= n - 1; i++) {
        int t = -1;
        // Find unvisited node with minimum distance
        for(int j = 1;j <= n; j++) {
            if(!vis[j] && (t == -1 || dist[j] < dist[t])) t = j;
        }
        vis[t] = true;
        // Update distances of t's neighbors
        for(int j = 1; j <= n; j++) {
            dist[j] = min(dist[j], dist[t] + g[t][j]);
        }
    }

    if(dist[n] == INF)  return -1;
    return dist[n];
}

int main()
{
    memset(g, 0x3f, sizeof g);
    cin >> n >> m;
    while(m--) {
        int x, y, z;
        cin >> x >> y >> z;
        g[x][y] = min(g[x][y], z);  // Handle multiple edges
    }
    cout << Dijkstra() << endl;
    return 0;
}