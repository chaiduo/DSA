// Tarjan Algorithm: Find Strongly Connected Components (SCC) in Directed Graph
// Time Complexity: O(n + m)
// Core: Use dfn (DFS order) and low (minimum DFS order reachable) to identify SCCs
// When low[x] == dfn[x], all nodes from x to stack top form an SCC

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10010;
vector<int> edge[N];
int dfn[N], low[N], tot;    // dfn: DFS order, low: minimum DFS order reachable
int stk[N], in_stk[N], top; // Stack, used to collect SCC
int scc[N], siz[N], scc_cnt; // scc[i]: SCC id of node i, siz: size of each SCC

void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk[++top] = x; in_stk[x] = 1;
    for(int y : edge[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);  // Backtrack update
        } else if(in_stk[y]) {
            low[x] = min(low[x], dfn[y]);  // Encounter node in stack, update low
        }
    }

    // low == dfn indicates found root of an SCC
    if(low[x] == dfn[x]) {
        int y; ++scc_cnt;
        do {
            y = stk[top--]; in_stk[y] = 0;
            scc[y] = scc_cnt;
            siz[scc_cnt]++;
        } while(y != x);
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
    }
    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) tarjan(i);

    return 0;
}