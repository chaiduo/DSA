// SPFA 算法（Shortest Path Faster Algorithm）：求单源最短路
// 时间复杂度：平均 O(m)，最坏 O(nm)
// 本质是 Bellman-Ford 的队列优化，可处理负权边
// 核心：只将距离更新过的点入队，避免无效松弛

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, m;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
vector<int>dist(N, INF);
vector<bool>vis(N, false);  // 标记是否在队列中
typedef pair<int, int> PII;
vector<vector<PII>>edges(N);

int spfa()
{ 
    queue<int> q;
    q.push(1);
    dist[1] = 0;
    vis[1] = true;
    while(!q.empty()) {
        int x = q.front();
        q.pop();
        vis[x] = false;  // 出队标记
        // 松弛 x 的所有邻居
        for(auto &[y, w] : edges[x]) {
            if(dist[x] + w < dist[y]) {
                dist[y] = dist[x] + w;
                if(!vis[y]) {
                    q.push(y);
                    vis[y] = true;  // 入队标记
                }
            }
        }
    }

    return dist[n] == INF ? -1 : dist[n];
}

int main()
{
    cin >> n >> m;
    while(m--) {
        int x, y, w;
        cin >> x >> y >> w;
        edges[x].push_back({y, w});
    }
    cout << spfa() << endl;
    return 0;
}