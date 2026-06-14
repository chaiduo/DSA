// Prim 算法：求最小生成树
// 时间复杂度 O(n^2)，适合稠密图
// 核心思想：每次选距离生成树最近的点加入，用该点更新其他点的距离
// 与 Dijkstra 类似，但 dist 维护的是到生成树的距离而非到起点的距离

#include <iostream>
#include <cstring>
using namespace std;
const int N = 510, INF = 0x3f3f3f3f;
int n, m;
int g[N][N], dist[N];  // g 为邻接矩阵，dist 为到生成树的最短距离
bool vis[N];

int prim()
{
    memset(dist, 0x3f, sizeof(dist));
    dist[0] = 0;  // 虚拟起点，距离为0
    int ans = 0;
    for(int i = 0; i < n; i++) {
        int t = -1;
        // 找到未访问中距离生成树最近的点
        for(int j = 1; j <= n; j++) 
            if(!vis[j] && (t == -1 || dist[j] < dist[t])) 
                t = j;

        if(i && dist[t] == INF) return INF;  // 图不连通
        ans += dist[t];
        
        vis[t] = true;
        // 用 t 更新其他点到生成树的距离
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
        g[b][a] = g[a][b] = min(g[a][b], w);  // 无向图
    }
    
    int t = prim();
    if(t == INF) cout << "impossible";
    else cout << t << endl;
    return 0;
}