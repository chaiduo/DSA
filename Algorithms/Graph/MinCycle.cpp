// Floyd-Warshall Algorithm for Finding Minimum Cycle in Undirected Graph
// Time Complexity: O(n^3)
// Key Idea: Enumerate the vertex k with maximum index on the cycle
// The cycle consists of: i->k, j->k, and shortest path from i to j
// Before the k-th iteration of Floyd, w[i][j] stores shortest path using only vertices 1~k-1
// Cycle length = w[i][j] + g[i][k] + g[j][k] (where i < k, j < k)
// Use array p to reconstruct the path

#include <iostream>
#include <cstring>
using namespace std;

const int N = 110, INF = 0x3f3f3f3f;
int g[N][N], w[N][N], p[N][N];  // g: adjacency matrix, w: shortest path matrix, p: path record
int cnt, path[N];

// Recursively reconstruct path from i to j
void get_path(int i, int j) {
    if(p[i][j] == 0) return ;
    int k = p[i][j];
    get_path(i, k);
    path[cnt++] = k;
    get_path(k, j);
}

int main()
{
    int n, m;
    cin >> n >> m;
    
    memset(g, 0x3f, sizeof g);
    for(int i = 0; i <= n; i++) g[i][i] = 0;
    while(m --) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a][b] = g[b][a] = min(c, g[a][b]);
    }
    
    int ans = INF;
    memcpy(w, g, sizeof g);
    for(int k = 1; k <= n; k++) {
        // Before k-th Floyd iteration, update minimum cycle using w[i][j] + g[i][k] + g[j][k]
        for(int i = 1; i < k; i++)
            for(int j = i + 1; j < k; j++)
                if((long long)w[i][j] + g[i][k] + g[j][k] < ans) {
                    ans = (long long)w[i][j] + g[i][k] + g[j][k];
                    cnt = 0;
                    path[cnt++] = k;
                    path[cnt++] = i;
                    get_path(i, j);
                    path[cnt++] = j;
                }
        
        // Standard Floyd-Warshall iteration
        for(int i = 1; i <= n; i++) 
            for(int j = 1; j <= n; j++) {
                if(w[i][j] > w[i][k] + w[k][j]) {
                    w[i][j] = w[i][k] + w[k][j];
                    p[i][j] = k;
                }
            }
    }
    if(ans == INF) cout << "No solution." << endl;
    else for(int i = 0; i < cnt; i++) cout << path[i] << " ";
    return 0;
}
