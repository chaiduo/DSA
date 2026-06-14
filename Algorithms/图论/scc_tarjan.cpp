// Tarjan 算法：求有向图的强连通分量（SCC）
// 时间复杂度 O(n + m)
// 核心：用 dfn（DFS序）和 low（能回溯到的最小DFS序）判断 SCC
// 当 low[x] == dfn[x] 时，栈中从 x 到栈顶的所有节点构成一个 SCC

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 10010;
vector<int> edge[N];
int dfn[N], low[N], tot;    // dfn: DFS序, low: 能回溯到的最小DFS序
int stk[N], in_stk[N], top; // 栈，用于收集 SCC
int scc[N], siz[N], scc_cnt; // scc[i]: 节点i所属SCC编号, siz: 各SCC大小

void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    stk[++top] = x; in_stk[x] = 1;
    for(int y : edge[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);  // 回溯更新
        } else if(in_stk[y]) {
            low[x] = min(low[x], dfn[y]);  // 遇到栈中节点，更新 low
        }
    }

    // low == dfn 说明找到了一个 SCC 的根
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