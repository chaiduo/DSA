// SPFA Algorithm (Shortest Path Faster Algorithm): Find Single-Source Shortest Path
// Time Complexity: Average O(m), Worst Case O(nm)
// Essentially a queue optimization of Bellman-Ford, can handle negative weight edges
// Core: Only enqueue nodes whose distance was updated, avoid unnecessary relaxations

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int n, m;
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
vector<int>dist(N, INF);
vector<bool>vis(N, false);  // Mark if node is in queue
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
        vis[x] = false;  // Mark as dequeued
        // Relax all neighbors of x
        for(auto &[y, w] : edges[x]) {
            if(dist[x] + w < dist[y]) {
                dist[y] = dist[x] + w;
                if(!vis[y]) {
                    q.push(y);
                    vis[y] = true;  // Mark as enqueued
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