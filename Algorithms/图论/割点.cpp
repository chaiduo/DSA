// Tarjan 算法求割点（无向图）
// 割点：删除该点后图的连通分量数增加
// 时间复杂度 O(n + m)
// 判定条件：
//   - 根节点：子节点数 > 1 则为割点
//   - 非根节点：存在子节点 y 使得 low[y] >= dfn[x]，则 x 为割点

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 20010;

int n, m, root;
vector<int> edge[N];
int dfn[N], low[N], tot;
bool cut[N];  // cut[i] 标记 i 是否为割点

void tarjan(int x) {
    dfn[x] = low[x] = ++tot;
    int child = 0;
    for(int y : edge[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x] = min(low[x], low[y]);
            if(low[y] >= dfn[x]) {  // y 无法回到 x 的祖先
                child++;
                if(x != root || child > 1) {  // 根节点需要至少2个子树
                    cut[x] = true;
                }
            }
        } else {
            low[x] = min(low[x], dfn[y]);  // 回边
        }
    }
}
int main()
{
    cin >> n >> m;
    while(m--) {
        int a, b;
        cin >> a >> b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    for(int i = 1; i <= n; i++) 
        if(!dfn[i]) {
            root = i;
            tarjan(i);
        }
    for(int i = 1; i <= n; i++)
        if(cut[i]) cout << i << " ";
    return 0;
}