// Dijkstra 算法（堆优化版）：求单源最短路（稀疏图）
// 时间复杂度 O(m log n)，适合稀疏图（邻接表存储）
// 核心：用优先队列（小根堆）优化找最小距离点的过程
// 不能处理负权边

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n, m;
const int N = 510, M = 100010;
const int inf = 1e9;
typedef pair<int,int> PII;  // {距离, 节点编号}
vector<int>dist(N, inf);
vector<bool>vis(N, false);
vector<vector<PII>>edges(N);  // 邻接表：edges[u] = {{v, w}, ...}

int Dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII>>q;  // 小根堆
    dist[1] = 0;
    q.push({0, 1});

    while(!q.empty()) {
        auto t = q.top();
        q.pop();
        int x = t.second;
        if(vis[x]) continue;  // 已确定最短路的点跳过
        vis[x] = true;
        // 用 x 更新其邻居
        for(auto& [y, w] : edges[x]) {
            int dis = dist[x] + w;
            if(dis < dist[y]) {
                dist[y] = dis;
                q.push({dis, y});  // 新距离入堆
            } 
        }
    }

    int ans = *max_element(dist.begin() + 1, dist.end());
    return ans == inf ? -1 : ans;
}
int main()
{
    cin >> n >> m;
    while(m--) {
        int x, y, z;
        cin >> x >> y >> z;
        edges[x].push_back({y, z});
    }
    cout << Dijkstra() << endl;
    return 0;
}
