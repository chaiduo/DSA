// Dijkstra 算法（朴素版）：求单源最短路（稠密图）
// 时间复杂度 O(n^2)，适合稠密图（邻接矩阵存储）
// 核心思想：每次选出距离最小的未访问节点，用其更新邻居
// 不能处理负权边

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
int n, m;
const int N = 510, M = 100010;
const int INF = 0x3f3f3f3f;
int g[N][N], dist[N];  // g 为邻接矩阵，dist 为到起点的距离
bool vis[N];

int Dijkstra()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;    
    // 迭代 n-1 次，每次确定一个点的最短路
    for(int i = 1; i <= n - 1; i++) {
        int t = -1;
        // 找到未访问中距离最小的点
        for(int j = 1;j <= n; j++) {
            if(!vis[j] && (t == -1 || dist[j] < dist[t])) t = j;
        }
        vis[t] = true;
        // 用 t 更新其邻居的距离
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
        g[x][y] = min(g[x][y], z);  // 处理重边
    }
    cout << Dijkstra() << endl;
    return 0;
}