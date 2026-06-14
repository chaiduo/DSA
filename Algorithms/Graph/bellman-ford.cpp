// Bellman-Ford Algorithm: Find Single-Source Shortest Path (with edge count limit)
// Time Complexity: O(n * m), can handle negative weight edges
// Feature: Can limit maximum k edges, suitable for shortest path problems with edge constraints
// Core: Each iteration relaxes all edges, use backup array to prevent cascading updates

#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, M = 10010;
struct Edge{
    int x, y, w;
} edge[M];

int n, m, k;
int dist[N], backup[N];  // backup prevents multiple relaxations in one iteration (cascading)

int bellman_ford()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    // Iterate k times, each time at most one more edge
    for(int i = 1; i <= k; i++) {
        memcpy(backup, dist, sizeof(dist));  // Backup previous iteration results
        for(int j = 0; j < m; j++) {
            int a = edge[j].x, b = edge[j].y, w = edge[j].w;
            dist[b] = min(dist[b], backup[a] + w);  // Relax using backup values
        }
    }
    return dist[n];
}

int main()
{
    cin >> n >> m >> k;
    for(int i = 0; i < m; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        edge[i] = {a, b, w};
    }
    
    int t = bellman_ford();
    if(t > 0x3f3f3f3f / 2 ) puts("impossible");  // Check if unreachable
    else cout << t << endl;
    return 0;
}