// Tarjan's Algorithm for Finding Bridges (Cut Edges) in Undirected Graph
// Bridge: An edge whose removal increases the number of connected components
// Time Complexity: O(n + m)
// Criteria: low[y] > dfn[x] (strictly greater, different from cut points)
// Uses edge indices to avoid going back through parent edge

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 160, M = 5010;
typedef pair<int,int> edge;

int n, m;
vector<edge> eg;       // Store all edges
vector<int> h[N];      // Adjacency list, stores edge indices
vector<edge>bridge;    // Store bridges
int dfn[N], low[N], tot;

void add(int a, int b) {
    eg.push_back({a, b});
    h[a].push_back(eg.size() - 1);  // Record edge index
}

// in_edge is the index of the edge used to enter current node, to avoid going back
void tarjan(int x, int in_edge) {
    dfn[x] = low[x] = ++tot;
    for(int i : h[x]) {
        int y = eg[i].second;
        if(!dfn[y]) {
            tarjan(y, i);
            low[x] = min(low[x], low[y]);
            if(low[y] > dfn[x]) bridge.push_back({x, y});  // Bridge found
        } else if(abs(i - in_edge) != 1) {  // Not the reverse of the same edge
            low[x] = min(low[x], dfn[y]);
        }
    }
}
int main()
{
    cin >> n >> m;
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        add(a, b); add(b, a);  // Store undirected edge as two directed edges
    }

    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) tarjan(i, -1);

    sort(bridge.begin(), bridge.end());
    for(auto t : bridge) cout << t.first << " " << t.second << endl;
    return 0;
}
