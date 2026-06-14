// Dijkstra Algorithm (Heap Optimized): Find Single-Source Shortest Path (Sparse Graph)
// Time Complexity: O(m log n), suitable for sparse graphs (adjacency list storage)
// Core: Use priority queue (min-heap) to optimize finding minimum distance node
// Cannot handle negative weight edges

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int n, m;
const int N = 510, M = 100010;
const int inf = 1e9;
typedef pair<int,int> PII;  // {distance, node index}
vector<int>dist(N, inf);
vector<bool>vis(N, false);
vector<vector<PII>>edges(N);  // Adjacency list: edges[u] = {{v, w}, ...}

int Dijkstra()
{
    priority_queue<PII, vector<PII>, greater<PII>>q;  // Min-heap
    dist[1] = 0;
    q.push({0, 1});

    while(!q.empty()) {
        auto t = q.top();
        q.pop();
        int x = t.second;
        if(vis[x]) continue;  // Skip nodes with determined shortest path
        vis[x] = true;
        // Update x's neighbors
        for(auto& [y, w] : edges[x]) {
            int dis = dist[x] + w;
            if(dis < dist[y]) {
                dist[y] = dis;
                q.push({dis, y});  // Push new distance to heap
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
