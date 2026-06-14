// Bellman-Ford 算法：求单源最短路（限制边数）
// 时间复杂度 O(n * m)，可处理负权边
// 特点：可限制最多经过 k 条边，适合解决有边数限制的最短路问题
// 核心：每轮遍历所有边进行松弛，用 backup 数组防止串联更新

#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, M = 10010;
struct Edge{
    int x, y, w;
} edge[M];

int n, m, k;
int dist[N], backup[N];  // backup 防止一轮中多次松弛（串联）

int bellman_ford()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[1] = 0;
    // 迭代 k 次，每次最多经过一条边
    for(int i = 1; i <= k; i++) {
        memcpy(backup, dist, sizeof(dist));  // 备份上一轮结果
        for(int j = 0; j < m; j++) {
            int a = edge[j].x, b = edge[j].y, w = edge[j].w;
            dist[b] = min(dist[b], backup[a] + w);  // 用备份值松弛
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
    if(t > 0x3f3f3f3f / 2 ) puts("impossible");  // 判断不可达
    else cout << t << endl;
    return 0;
}