// Tarjan 缩点 + DAG 上 DP
// 先用 Tarjan 求 SCC 并缩点，将原图转化为 DAG
// 然后在 DAG 上按拓扑序 DP，求最大点权和路径
// 应用：如"受欢迎的牛"等需要 SCC 缩点的题目

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10010;
vector<int> edge[N];   // 原图
vector<int> nedge[N];  // 缩点后的 DAG
int dfn[N], low[N], tot;
int stk[N], in_stk[N], top;
int scc[N], siz[N], scc_cnt;
int dp[N], w[N], nw[N];  // w: 原点权, nw: SCC 点权, dp: DAG 上 DP

// Tarjan 求 SCC
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

    // 构建缩点后的 DAG
    for(int x = 1; x <= n; x++) {
        nw[scc[x]] += w[x];  // SCC 的点权为内部点权之和
        for(int y : edge[x]) 
            if(scc[x] != scc[y]) 
                nedge[scc[x]].push_back(scc[y]);
    }

    // DAG 上 DP（SCC 编号即为拓扑序的逆序）
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