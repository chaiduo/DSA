// Tarjan's Algorithm for SCC Condensation + DAG DP
// First use Tarjan to find SCCs and condense the graph into a DAG
// Then perform DP on the DAG in topological order to find max path weight
// Application: Problems like "Popular Cows" that require SCC condensation

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10010;
vector<int> edge[N];   // Original graph
vector<int> nedge[N];  // DAG after condensation
int dfn[N], low[N], tot;
int stk[N], in_stk[N], top;
int scc[N], siz[N], scc_cnt;
int dp[N], w[N], nw[N];  // w: original vertex weight, nw: SCC weight, dp: DAG DP

// Tarjan's algorithm to find SCCs
void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk[++top] = x; in_stk[x] = 1;
    for(int y : edge[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
        } else if(in_stk[y]) {
            low[x] = min(low[x], dfn[y]);
        }
    }

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
    for(int i = 1; i <= n; i++) cin >> w[i];
    while(m--) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
    }
    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) tarjan(i);

    // Build DAG after condensation
    for(int x = 1; x <= n; x++) {
        nw[scc[x]] += w[x];  // SCC weight is sum of internal vertex weights
        for(int y : edge[x])
            if(scc[x] != scc[y])
                nedge[scc[x]].push_back(scc[y]);
    }

    // DP on DAG (SCC number is the reverse of topological order)
    for(int i = scc_cnt; i; i--) {
        if(dp[i] == 0) dp[i] = nw[i];
        for(int x : nedge[i])
            dp[x] = max(dp[x], dp[i] + nw[x]);
    }
    
    int ans = 0;
    for(int i = 1; i <= n; i++)
        ans = max(ans, dp[i]);
    cout << ans << endl;
    return 0;
}