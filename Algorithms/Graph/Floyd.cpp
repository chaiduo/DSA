// Floyd-Warshall Algorithm: Find All-Pairs Shortest Paths
// Time Complexity: O(n^3), Space Complexity: O(n^2)
// Core Idea: Enumerate intermediate vertex k, update shortest distance for all pairs (i,j)
// dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])

#include <iostream>
using namespace std;
int n, m;
const int N = 500, M = 100000;
int dist[N][N];

// Floyd main loop: k is the intermediate vertex
void floyd()
{
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}
int main()
{
    int x, y, z;
    cin >> n >> m;
    while(m--) {
        cin >> x >> y >> z;
        dist[x][y] = z;
    }
    floyd();
    cout << dist[1][n] << endl;
    return 0;
}
