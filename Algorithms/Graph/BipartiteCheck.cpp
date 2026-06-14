// Bipartite Graph Check using Coloring Method
// Time Complexity: O(n + m)
// Key Idea: A graph is bipartite if and only if it can be 2-colored
// (adjacent vertices have different colors)
// Use DFS to attempt 2-coloring; if conflict occurs, it's not bipartite

#include <iostream>
#include <vector>
using namespace std;
const int N = 100010;
int n, m;
vector<vector<int>>g(N);
int color[N]; // 0: uncolored, 1: color 1, -1: color -1

// DFS coloring, idx is current node, cor is its color
bool dfs(int idx, int cor)
{
    for(auto x : g[idx]) {
        if(!color[x]) {
            color[x] = cor;       // Color with opposite color
            if(!dfs(x, -cor)) return false;
        } else if(color[x] != cor) {
            return false;          // Adjacent nodes have same color, conflict
        }
    }
    return true;
}
int main()
{
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    
    for(int i = 1; i <= n; i++) {
        if(!color[i]) {
            color[i] = 1;
            if(!dfs(i, -1)) {
                cout << "No";
                return 0;
            }
        }
    }
    cout << "Yes";
    return 0;
}